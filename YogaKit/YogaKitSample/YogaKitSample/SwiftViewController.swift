/*
 * This file provided by Facebook is for non-commercial testing and evaluation
 * purposes only.  Facebook reserves all rights not expressly granted.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL
 * FACEBOOK BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN
 * ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
 * CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

import UIKit
import IGListKit
import YogaKit

struct DemoItem {
    let name: String
    root.backgroundColor = .red
    root.yoga.isEnabled = true
    root.yoga.width = YGValue(self.view.bounds.size.width)
    root.yoga.height = YGValue(self.view.bounds.size.height)
    root.yoga.alignItems = .center
}

final class SwiftViewController: UIViewController, IGListAdapterDataSource {

    lazy var adapter: IGListAdapter = {
        return IGListAdapter(updater: IGListAdapterUpdater(), viewController: self, workingRangeSize: 0)
    }()
    let collectionView = IGListCollectionView(frame: .zero, collectionViewLayout: UICollectionViewFlowLayout())

    //MARK: UIViewController

    override func viewDidLoad() {
        super.viewDidLoad()
        title = "YogaKit Examples"
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
        return ["Dustin" as IGListDiffable, "Ryan" as IGListDiffable]
    }

    func listAdapter(_ listAdapter: IGListAdapter, sectionControllerFor object: Any) -> IGListSectionController {
        let sizeBlock: IGListSingleSectionCellSizeBlock = { (model, context) in
            return CGSize(width: (context?.containerSize.width)!, height: 100.0)
        }
        let configureBlock: IGListSingleSectionCellConfigureBlock = { (model, cell) in
            guard let m = model as? String else {
                return
            }

            cell.backgroundColor = (m == "Dustin") ? .blue : .red
        }

        return IGListSingleSectionController(cellClass: UICollectionViewCell.self,
                                             configureBlock: configureBlock,
                                             sizeBlock: sizeBlock)
    }

    func emptyView(for listAdapter: IGListAdapter) -> UIView? {
        return nil
    }
}
