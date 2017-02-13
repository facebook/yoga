/**
 * Copyright 2014-present, Facebook, Inc.
 * All rights reserved.
 *
 * This source code is licensed under the license found in the
 * LICENSE-examples file in the root directory of this source tree.
 */

import UIKit
import YogaKit

final class SingleLabelCollectionCell: UICollectionViewCell {
    let label: UILabel = UILabel(frame: .zero)

    override init(frame: CGRect) {
        super.init(frame: frame)

        contentView.yoga.isEnabled = true
        contentView.yoga.flexDirection = .column
        contentView.yoga.justifyContent = .flexEnd

        label.textAlignment = .center
        label.numberOfLines = 1
        label.yoga.isIncludedInLayout = false
        contentView.addSubview(label)

        let border = UIView(frame: .zero)
        border.backgroundColor = .lightGray
        border.yoga.isEnabled = true
        border.yoga.height = 0.5
        border.yoga.marginHorizontal = 25
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
