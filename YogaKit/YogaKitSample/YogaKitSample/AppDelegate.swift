/**
 * Copyright 2014-present, Facebook, Inc.
 * All rights reserved.
 *
 * This source code is licensed under the license found in the
 * LICENSE-examples file in the root directory of this source tree.
 */

import Foundation
import UIKit

@UIApplicationMain
class AppDelegate: UIResponder, UIApplicationDelegate {
    var window: UIWindow?

    func applicationDidFinishLaunching(_ application: UIApplication) {
        self.window = UIWindow(frame: UIScreen.main.bounds)
        if let window = self.window {
            let navigationController = UINavigationController(rootViewController: ExamplesViewController())
            navigationController.navigationBar.isTranslucent = false

            window.rootViewController = navigationController
            window.backgroundColor = .white
            window.makeKeyAndVisible()
        }
    }
}
