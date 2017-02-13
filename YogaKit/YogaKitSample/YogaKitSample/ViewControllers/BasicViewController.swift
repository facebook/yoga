/**
 * Copyright 2014-present, Facebook, Inc.
 * All rights reserved.
 *
 * This source code is licensed under the license found in the
 * LICENSE-examples file in the root directory of this source tree.
 */

import UIKit
import YogaKit

final class BasicViewController: UIViewController {
    override func viewDidLoad() {
        let containerSize = self.view.bounds.size

        let root = self.view!
        root.backgroundColor = .white
        root.yoga.isEnabled = true
        root.yoga.width = containerSize.width
        root.yoga.height = containerSize.height
        root.yoga.alignItems = .center
        root.yoga.justifyContent = .center

        let child1 = UIView()
        child1.backgroundColor = .blue
        child1.yoga.isEnabled = true
        child1.yoga.width = 100
        child1.yoga.height = 10
        child1.yoga.marginBottom = 25
        root.addSubview(child1)

        let child2 = UIView()
        child2.yoga.isEnabled = true
        child2.yoga.alignSelf = .flexEnd
        child2.backgroundColor = .green
        child2.frame = CGRect(x: 0, y: 0, width: 200, height: 100)
        root.addSubview(child2)

        let child3 = UIView()
        child3.yoga.isEnabled = true
        child3.yoga.alignSelf = .flexStart
        child3.backgroundColor = .yellow
        child3.frame = CGRect(x: 0, y: 0, width: 100, height: 100)
        root.addSubview(child3)

        root.yoga.applyLayout(preservingOrigin: true)
    }
}
