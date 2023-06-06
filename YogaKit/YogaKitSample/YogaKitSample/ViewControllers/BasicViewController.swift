/*
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 */

import UIKit
import YogaKit

final class BasicViewController: UIViewController {
    override func viewDidLoad() {
        super.viewDidLoad()
        let containerSize = self.view.bounds.size

        view.backgroundColor = UIColor.systemBackground
        view.configureLayout { (layout) in
            layout.isEnabled = true
            layout.width = YGValue(containerSize.width)
            layout.height = YGValue(containerSize.height)
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
        view.addSubview(child1)

        let child2 = UIView(frame: CGRect(x: 0, y: 0, width: 200, height: 200))
        child2.backgroundColor = .green
        child2.configureLayout { (layout) in
            layout.isEnabled = true
            layout.alignSelf = .flexEnd
            layout.width = 200
            layout.height = 200
        }
        view.addSubview(child2)

        let child3 = UIView(frame: CGRect(x: 0, y: 0, width: 100, height: 100))
        child3.backgroundColor = .yellow
        child3.configureLayout { (layout) in
            layout.isEnabled = true
            layout.alignSelf = .flexStart
            layout.width = 100
            layout.height = 100

        }
        view.addSubview(child3)

        view.yoga.applyLayout(preservingOrigin: true)
    }
}
