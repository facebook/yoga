//
//  AutoLayoutMixedViewController.swift
//  YogaKitSample
//
//  Created by lvv on 2020/8/15.
//  Copyright © 2020 facebook. All rights reserved.
//

import UIKit
import YogaKit

class AutoLayoutMixedViewController : UIViewController {
    override func viewDidLoad() {
        super.viewDidLoad()

        view.configureLayout { (layout) in
            layout.isEnabled = true
            layout.alignItems = .center
            layout.justifyContent = .center
        }

        let container = UIView()
        container.backgroundColor = .orange
        container.configureLayout { (layout) in
            layout.isEnabled = true

            layout.paddingTop = 20
            layout.paddingLeft = 20
            layout.paddingBottom = 20
            layout.paddingRight = 70

            layout.width = 100%
        }
        view.addSubview(container)

        let subView1 = UIView()
        subView1.backgroundColor = .red
        subView1.configureLayout { (layout) in
            layout.isEnabled = true
            layout.height = 30;
        }
        container.addSubview(subView1)

        let subView2 = UIView()
        subView2.backgroundColor = .yellow
        subView2.configureLayout { (layout) in
            layout.isEnabled = true
            layout.marginTop = 25
            layout.height = 10;
        }
        container.addSubview(subView2)

        let subView3 = UIView()
        subView3.backgroundColor = .blue
        subView3.configureLayout { (layout) in
            layout.isEnabled = true
            layout.marginTop = 25
            layout.height = 20;
        }
        container.addSubview(subView3)

        let subView4 = UIView()
        subView4.backgroundColor = .green
        subView4.translatesAutoresizingMaskIntoConstraints = false
        container.addSubview(subView4)

        container.addConstraints([
            NSLayoutConstraint(item: subView4, attribute: .right, relatedBy: .equal, toItem: container, attribute: .right, multiplier: 1, constant: -10),
            NSLayoutConstraint(item: subView4, attribute: .centerY, relatedBy: .equal, toItem: container, attribute: .centerY, multiplier: 1, constant: 0),
            NSLayoutConstraint(item: subView4, attribute: .width, relatedBy: .equal, toItem: nil, attribute: .notAnAttribute, multiplier: 1, constant: 50),
            NSLayoutConstraint(item: subView4, attribute: .height, relatedBy: .equal, toItem: nil, attribute: .notAnAttribute, multiplier: 1, constant: 50)
        ])
    }
}
