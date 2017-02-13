/**
 * Copyright 2014-present, Facebook, Inc.
 * All rights reserved.
 *
 * This source code is licensed under the license found in the
 * LICENSE-examples file in the root directory of this source tree.
 */

import UIKit
import YogaKit

final class LayoutInclusionViewController: UIViewController {
    private let button: UIButton = UIButton(type: .system)
    private let disappearingView: UIView = UIView(frame: .zero)
    private let contentView: UIView = UIView(frame: .zero)

    override func viewDidLoad() {
        let root = self.view!
        root.backgroundColor = .white
        root.yoga.isEnabled = true
        root.yoga.flexDirection = .column
        root.yoga.justifyContent = .spaceAround

        contentView.backgroundColor = .clear
        contentView.layer.borderColor = UIColor.lightGray.cgColor
        contentView.layer.borderWidth = 1.0
        contentView.yoga.isEnabled = true
        contentView.yoga.height = 300
        contentView.yoga.width = self.view.bounds.size.width
        contentView.yoga.flexDirection = .row
        contentView.yoga.justifyContent = .center
        contentView.yoga.paddingHorizontal = 25
        self.view.addSubview(contentView)

        let redView = UIView(frame: .zero)
        redView.backgroundColor = .red
        redView.yoga.isEnabled = true
        redView.yoga.flexGrow = 1
        redView.yoga.flexShrink = 1
        contentView.addSubview(redView)

        disappearingView.backgroundColor = .blue
        disappearingView.yoga.isEnabled = true
        disappearingView.yoga.flexGrow = 1
        contentView.addSubview(disappearingView)

        button.setTitle("Add Blue View", for: UIControlState.selected)
        button.setTitle("Remove Blue View", for: UIControlState.normal)
        button.addTarget(self, action: #selector(buttonWasTapped), for: UIControlEvents.touchUpInside)
        button.yoga.isEnabled = true
        button.yoga.height = 300
        button.yoga.width = 300
        button.yoga.alignSelf = .center
        root.addSubview(button)

        root.yoga.applyLayout(preservingOrigin: false)
    }

    // MARK - UIButton Action
    func buttonWasTapped() {
        button.isSelected = !button.isSelected

        button.isUserInteractionEnabled = false
        disappearingView.yoga.isIncludedInLayout = !disappearingView.yoga.isIncludedInLayout
        disappearingView.isHidden = !disappearingView.isHidden

        contentView.yoga.applyLayout(preservingOrigin: true)
        button.isUserInteractionEnabled = true
    }
}
