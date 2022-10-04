/*
 * Copyright (c) Facebook, Inc. and its affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 */

import UIKit
import YogaKit

final class SingleLabelCollectionCell: UICollectionViewCell {
    let label: UILabel = UILabel(frame: .zero)

    override init(frame: CGRect) {
        super.init(frame: frame)

        contentView.configureLayout { (layout) in
            layout.isEnabled = true
            layout.flexDirection = .column
            layout.justifyContent = .flexEnd
        }

        label.textAlignment = .center
        label.numberOfLines = 1
        label.yoga.isIncludedInLayout = false
        contentView.addSubview(label)

        let border = UIView(frame: .zero)
        border.backgroundColor = .lightGray
        border.configureLayout { (layout) in
            layout.isEnabled = true
            layout.height = 0.5
            layout.marginHorizontal = 25
        }
        contentView.addSubview(border)
    }

    required init?(coder aDecoder: NSCoder) {
        fatalError("init(coder:) has not been implemented")
    }

    override func layoutSubviews() {
        super.layoutSubviews()

        contentView.yoga.applyLayout(preservingOrigin: false)
        label.frame = contentView.bounds
    }
}
