//
//  UDCompletedJobsViewController.swift
//  UDeli
//
//  Created by ARXT Labs on 10/4/18.
//  Copyright © 2018 ARXT Labs. All rights reserved.
//

import UIKit
import Material

class UDCompletedJobsViewController: UIViewController {
    @IBOutlet weak var toolBar: Toolbar!
    fileprivate var backButton: IconButton!
    override func viewDidLoad() {
        super.viewDidLoad()
        setNeedsStatusBarAppearanceUpdate()
        self.loadInitialData()
    }
    
    // MARK:- View Lifecycle
    override func didReceiveMemoryWarning() {
        super.didReceiveMemoryWarning()
    }
    
    override var preferredStatusBarStyle: UIStatusBarStyle {
        return .lightContent
    }
    
    func loadInitialData() {
        let data = UserDefaults.standard.object(forKey:"userInfo") as! Data
        userInfoDictionary = (NSKeyedUnarchiver.unarchiveObject(with: data) as! NSMutableDictionary?)!
        prepareBackButton()
        prepareToolbar()
        getMyCompletedJobs()
    }
    
    func getMyCompletedJobs() {
        let merchantId = userInfoDictionary.object(forKey: "merchantid") as? Int ?? 0
        let userId = userInfoDictionary.object(forKey: "carrierid") as? Int ?? 0
        OrdersModel.getMyCompletedOrdersDetails(acceptedby: userId, merchantId: merchantId) { connectionResult in
            DispatchQueue.main.async(execute: {() -> Void in
                ConstantTools.sharedConstantTool.hideMRIndicatorView()
                //self.refreshControl.endRefreshing()
                switch connectionResult {
                case .success(let data):
                    print(data)
                    //self.myJobsArray = data
                    //self.noDataLabel.isHidden = true
                    //self.tableView.isHidden = false
                    //self.tableView.reloadData()
                case .failure(let error):
                    //self.noDataLabel.isHidden = false
                    //self.tableView.isHidden = true
                    self.view.makeToast(error, position: .top)
                }
            })
        }
    }
}

// MARK:- ToolBar
extension UDCompletedJobsViewController {
    fileprivate func prepareBackButton() {
        backButton = IconButton(image: Icon.cm.arrowBack, tintColor: .white)
        backButton.pulseColor = .white
        backButton.addTarget(self, action: #selector(navigateBack(button:)), for: .touchUpInside)
    }
    
    fileprivate func prepareToolbar() {
        toolBar.titleLabel.textColor = #colorLiteral(red: 1, green: 1, blue: 1, alpha: 1)
        toolBar.titleLabel.textAlignment = .left
        toolBar.leftViews = [backButton]
    }
    
    @objc
    fileprivate func navigateBack(button: UIButton) {
        self.navigationController!.popViewController(animated: true)
    }
}
