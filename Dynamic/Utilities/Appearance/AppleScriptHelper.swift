//
//  AppleScriptHelper.swift
//  Dynamic
//
//  Created by Apollo Zhu on 6/7/18.
//  Copyright © 2018 Dynamic Dark Mode. All rights reserved.
//

import AppKit

// MARK: - All Apple Scripts

public enum AppleScript: String, CaseIterable {
    case toggleDarkMode = "toggle"
    case enableDarkMode = "on"
    case disableDarkMode = "off"
}

// MARK: - Handy Properties

extension AppleScript {
    fileprivate var name: String {
        return "\(rawValue).scpt"
    }
    
    fileprivate static var folder: URL {
        return Bundle.main.resourceURL!
    }
    
    fileprivate var url: URL {
        return AppleScript.folder.appendingPathComponent(name)
    }
}

// MARK: - Execution

extension AppleScript {
    public func execute(then handle: @escaping ((Error?) -> Void) = showError) {
        AppleScript.checkPermission {
            var errorInfo: NSDictionary? = nil
            let script = NSAppleScript(contentsOf: self.url, error: &errorInfo)
            script?.executeAndReturnError(&errorInfo)
            showError(errorInfo)
        }
    }
}

extension AppleScript {
    public static func checkPermission(
        executeWhenAuthorized onSuccess: @escaping () -> Void = { }
    ) {
        requestPermission { authorized in
            if authorized { return onSuccess() }
            showErrorThenRedirect()
        }
    }

    public static func showErrorThenRedirect() {
        runModal(ofNSAlert: { alert in
            alert.alertStyle = .critical
            alert.messageText = NSLocalizedString(
                "AppleScript.authorization.error",
                value: "You didn't allow Dynamic Dark Mode to manage dark mode",
                comment: ""
            )
            #warning("Remove the RESTART line when apple has solved the bug.")
            alert.informativeText = NSLocalizedString(
                "AppleScript.authorization.instruction",
                value: """
We'll take you to System Preferences.
You may need to RESTART Dynamic Dark Mode to allow the new settings take effect.
""",
                comment: ""
            )
        }, then: { _ in
            redirectToSystemPreferences()
        })
    }

    public static func redirectToSystemPreferences() {
        NSWorkspace.shared.open(URL(string: "x-apple.systempreferences:com.apple.preference.security?Privacy_Automation")!)
    }

    public static func requestPermission(
        then process: @escaping (_ authorized: Bool) -> Void
    ) {
        DispatchQueue.global().async {
            let systemEvents = "com.apple.systemevents"
            // We need to get it running to send it messages
            NSWorkspace.shared.launchApplication(
                withBundleIdentifier: systemEvents,
                additionalEventParamDescriptor: nil,
                launchIdentifier: nil
            )
            let target = NSAppleEventDescriptor(bundleIdentifier: systemEvents)
            let status = AEDeterminePermissionToAutomateTarget(
                target.aeDesc, typeWildCard, typeWildCard, true
            )
            switch Int(status) {
            case Int(noErr):
                return process(true)
            case errAEEventNotPermitted:
                break
            case errOSAInvalidID:
                #warning("Figure out what causes this")
                runModal(ofNSAlert: { alert in
                    alert.messageText = NSLocalizedString(
                        "AppleScript.errorOSInvalidID",
                        value: "Something Went Wrong",
                        comment: "Please try again"
                    )
                })
            case errAEEventWouldRequireUserConsent, procNotFound:
                showCriticalErrorMessage("\(status)")
            default:
                log(.error, "Dynamic - Unhandled OSStatus")
            }
            process(false)
        }
    }
}
