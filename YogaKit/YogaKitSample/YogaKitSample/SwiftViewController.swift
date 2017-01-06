//
//  SwiftViewController.swift
//  YogaKitSample
//
//  Created by David Hart on 05.01.17.
//  Copyright © 2017 facebook. All rights reserved.
//

import UIKit

class SwiftViewController: UIViewController {
  override func viewDidLoad() {
    let root = self.view!
    root.backgroundColor = .red
    root.yoga.isEnabled = true
    root.yoga.width = self.view.bounds.size.width
    root.yoga.height = self.view.bounds.size.height
    root.yoga.alignItems = .center
    root.yoga.justifyContent = .center
    
    let child1 = UIView()
    child1.backgroundColor = .blue
    child1.yoga.isEnabled = true
    child1.yoga.width = 100
    child1.yoga.height = 10
    
    let child2 = UIView()
    child2.backgroundColor = .green
    child2.frame = CGRect(x: 0, y: 0, width: 200, height: 100)
    
    let child3 = UIView()
    child3.backgroundColor = .yellow
    child3.frame = CGRect(x: 0, y: 0, width: 100, height: 100)
    
    child2.addSubview(child3)
    root.addSubview(child1)
    root.addSubview(child2)
    root.yoga.applyLayout()
  }
}
