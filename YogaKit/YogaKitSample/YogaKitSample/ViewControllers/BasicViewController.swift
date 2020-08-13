/*
 * Copyright (c) Facebook, Inc. and its affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 */

import UIKit
import YogaKit

final class BasicViewController: UIViewController {
    override func viewDidLoad() {

        let root = self.view!
        root.backgroundColor = .white
        root.configureLayout { (layout) in
            layout.isEnabled = true
            layout.alignItems = .center
            layout.justifyContent = .center
        }

        let child1 = UIView()
        child1.backgroundColor = .blue
        child1.configureLayout { (layout) in
            layout.isEnabled = true
            layout.width = 100
            layout.height = 10
            layout.marginBottom = 25
        }
        root.addSubview(child1)

        let child2 = UIView()
        child2.backgroundColor = .green
        child2.configureLayout { (layout) in
            layout.isEnabled = true
            layout.alignSelf = .flexEnd
            layout.width = 200
            layout.height = 200
        }
        root.addSubview(child2)

        let child3 = UIView()
        child3.backgroundColor = .yellow
        child3.configureLayout { (layout) in
            layout.isEnabled = true
            layout.alignSelf = .flexStart
            layout.width = 100
            layout.height = 100
        }
        root.addSubview(child3)
    }
}
