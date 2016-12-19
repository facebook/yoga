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
        root.layout.isEnabled = true
        root.layout.width = view.bounds.size.width
        root.layout.height = view.bounds.size.height
        root.layout.alignItems = .center
        root.layout.justifyContent = .center
      
        let child1 = UIView()
        child1.backgroundColor = .blue
        child1.layout.isEnabled = true
        child1.layout.width = 100
        child1.layout.height = 100
      
        let child2 = UIView()
        child2.backgroundColor = .green
        child2.frame = CGRect(origin: .zero, size: CGSize(width: 200, height: 100))
      
        let child3 = UIView()
        child3.backgroundColor = .yellow
        child3.frame = CGRect(origin: .zero, size: CGSize(width: 100, height: 100))
      
        child2.addSubview(child3)
        root.addSubview(child1)
        root.addSubview(child2)
        root.layout.apply()
    }
}
