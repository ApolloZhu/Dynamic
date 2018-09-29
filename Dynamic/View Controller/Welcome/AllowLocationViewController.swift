//
//  AllowLocationViewController.swift
//  Dynamic
//
//  Created by Apollo Zhu on 9/28/18.
//  Copyright © 2018 Dynamic Dark Mode. All rights reserved.
//

import Cocoa
import CoreLocation


class AllowLocationViewController: NSViewController, SetupStep {

    @IBOutlet weak var showPreferences: NSButton!

    private lazy var manager: CLLocationManager = {
        let manager = CLLocationManager()
        manager.delegate = self
        return manager
    }()

    var isNotAuthorized: Bool {
        switch CLLocationManager.authorizationStatus() {
        case .authorizedAlways:
            showNextOnce()
            return false
        case .denied, .notDetermined, .restricted:
            return true
        }
    }

    override func viewDidAppear() {
        super.viewDidAppear()
        guard isNotAuthorized else { return }
        showPreferences.isHidden = false
        manager.requestLocation()
    }

    // MARK: - Navigation

    @IBAction func skip(_ sender: Any) {
        showNextOnce()
    }

    @IBAction func openPreferences(_ sender: NSButton) {
        redirectToSystemPreferences()
    }

    private var notShown = true

    func showNextOnce() {
        manager.delegate = nil
        guard notShown else { return }
        notShown = false
        showNext()
    }
}

fileprivate func redirectToSystemPreferences() {
    NSWorkspace.shared.open(URL(string: "x-apple.systempreferences:com.apple.preference.security?Privacy_LocationServices")!)
}

// MARK: - Delegate Implementation

extension AllowLocationViewController: CLLocationManagerDelegate {
    func locationManager(_ manager: CLLocationManager,
                         didUpdateLocations locations: [CLLocation]) {
        guard locations.first != nil else { return }
        showNextOnce()
    }

    func locationManager(_ manager: CLLocationManager,
                         didFailWithError error: Error) {
        runModal(ofNSAlert: { alert in
            alert.messageText = LocalizedString.Location.notAvailable
            alert.addButton(withTitle: NSLocalizedString(
                "SystemPreferences.open",
                value: "Open System Preferences",
                comment: ""
            ))
            alert.addButton(withTitle: NSLocalizedString(
                "SystemPreferences.skip",
                value: "Skip",
                comment: ""
            ))
            alert.alertStyle = .warning
        }, then: { [weak self] response in
            switch response {
            case .alertFirstButtonReturn:
                redirectToSystemPreferences()
            case .alertSecondButtonReturn:
                self?.showNextOnce()
            default:
                log(.error, "Dynamic - Unhandled Location Request Response")
            }
        })
    }

    func locationManager(_ manager: CLLocationManager,
                         didChangeAuthorization status: CLAuthorizationStatus) {
        if status == .authorizedAlways {
            showNextOnce()
        }
    }
}
