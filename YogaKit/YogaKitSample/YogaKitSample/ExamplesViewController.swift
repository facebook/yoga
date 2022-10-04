/*
 * Copyright (c) Facebook, Inc. and its affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 */

import UIKit
import IGListKit

private final class ExampleModel {
    let title: String
    let controllerClass: UIViewController.Type

    init(title: String, controllerClass: UIViewController.Type) {
        self.title = title
        self.controllerClass = controllerClass
    }
}

extension ExampleModel: IGListDiffable {
    fileprivate func diffIdentifier() -> NSObjectProtocol {
        return title as NSString
    }

    fileprivate func isEqual(toDiffableObject object: IGListDiffable?) -> Bool {
        guard let otherObj = object as? ExampleModel else { return false }

        return (title == otherObj.title) &&
               (controllerClass == otherObj.controllerClass)
    }
}

final class ExamplesViewController: UIViewController, IGListAdapterDataSource, IGListSingleSectionControllerDelegate {
    private lazy var adapter: IGListAdapter = {
        return IGListAdapter(updater: IGListAdapterUpdater(), viewController: self, workingRangeSize: 0)
    }()
    private let collectionView = IGListCollectionView(frame: .zero, collectionViewLayout: UICollectionViewFlowLayout())


    // Update this to array to create more examples.
    private let models: [ExampleModel] = [ExampleModel(title: "Basic Layout", controllerClass: BasicViewController.self),
                                          ExampleModel(title: "Exclude Views in Layout", controllerClass: LayoutInclusionViewController.self)]

    //MARK: UIViewController

    override func viewDidLoad() {
        super.viewDidLoad()
        title = "Examples"
        view.addSubview(collectionView)
        adapter.collectionView = collectionView
        adapter.dataSource = self
    }

    override func viewDidLayoutSubviews() {
        super.viewDidLayoutSubviews()
        collectionView.frame = view.bounds
    }

    //MARK: IGListAdapterDataSource

    func objects(for listAdapter: IGListAdapter) -> [IGListDiffable] {
        return models as [IGListDiffable]
    }

    func listAdapter(_ listAdapter: IGListAdapter, sectionControllerFor object: Any) -> IGListSectionController {
        let sizeBlock: IGListSingleSectionCellSizeBlock = { (model, context) in
            return CGSize(width: (context?.containerSize.width)!, height: 75.0)
        }

        let configureBlock: IGListSingleSectionCellConfigureBlock = { (model, cell) in
            guard let m = model as? ExampleModel, let c = cell as? SingleLabelCollectionCell else {
                return
            }

            c.label.text = m.title
        }

        let sectionController = IGListSingleSectionController(cellClass: SingleLabelCollectionCell.self,
                                                              configureBlock: configureBlock,
                                                              sizeBlock: sizeBlock)
        sectionController.selectionDelegate = self
        return sectionController
    }

    func emptyView(for listAdapter: IGListAdapter) -> UIView? { return nil }

    //MARK: IGListSingleSectionControllerDelegate

    func didSelect(_ sectionController: IGListSingleSectionController) {
        let section = adapter.section(for: sectionController)
        let model = models[section]

        let controller = model.controllerClass.init()
        controller.title = model.title

        self.navigationController?.pushViewController(controller, animated: true)
    }
}
