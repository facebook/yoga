//
//  SwiftViewController.swift
//  YogaKit
//
//  Created by David Hart on 18.12.16.
//  Copyright © 2016 facebook. All rights reserved.
//

import UIKit
import YogaKit

class SwiftViewController : UIViewController {
    override func viewDidLoad() {
        let root = view!
        root.backgroundColor = .red
        root.usesYoga = true
        root.layoutWidth = view.bounds.size.width
        root.layoutHeight = view.bounds.size.height
        root.layoutAlignItems = .center
        root.layoutJustifyContent = .center
      
        let child1 = UIView()
        child1.backgroundColor = .blue
        child1.usesYoga = true
        child1.layoutWidth = 100
        child1.layoutHeight = 100
      
        let child2 = UIView()
        child2.backgroundColor = .green
        child2.frame = CGRect(origin: .zero, size: CGSize(width: 200, height: 100))
      
        let child3 = UIView()
        child3.backgroundColor = .yellow
        child3.frame = CGRect(origin: .zero, size: CGSize(width: 100, height: 100))
      
        child2.addSubview(child3)
        root.addSubview(child1)
        root.addSubview(child2)
        root.applyLayout()
    }
}
