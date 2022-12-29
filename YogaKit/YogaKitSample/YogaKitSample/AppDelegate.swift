/*
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
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
