//
//  AppleScriptHelper.swift
//  Dynamic Dark Mode
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
    private var name: String {
        return "\(rawValue).scpt"
    }
    
    private static var folder: URL {
        return Bundle.main.resourceURL!
    }
    
    private var url: URL {
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
            showError(errorInfo, title: NSLocalizedString(
                "AppleScript.execute.error",
                comment: "something went wrong. But it's okay"
            ))
        }
    }
}

extension AppleScript {
    public static func checkPermission(
        onSuccess: @escaping () -> Void = { }
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
                comment: ""
            )
            #warning("Remove the RESTART line when apple has solved the bug.")
            alert.informativeText = NSLocalizedString(
                "AppleScript.authorization.instruction",
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
        retryOnInternalError: Bool = true,
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
            case errOSAInvalidID, -1751,
                 errAEEventWouldRequireUserConsent,
                 procNotFound:
                #warning("Figure out what causes this")
                if retryOnInternalError {
                    log(.error, "Dynamic Dark Mode - OSStatus %{public}d", status)
                    requestPermission(retryOnInternalError: false, then: process)
                } else {
                    runModal(ofNSAlert: { alert in
                        alert.messageText = NSLocalizedString(
                            "AppleScript.authorization.failed",
                            comment: "Generic error happened"
                        )
                        alert.informativeText = "\(status)"
                    })
                }
            default:
                log(.fault, "Dynamic Dark Mode - Unhandled OSStatus %{public}d", status)
                showCriticalErrorMessage("\(status)")
            }
            process(false)
        }
    }
}
