//
//  UDMyOrdersViewController.swift
//  UDeli
//
//  Created by ARXT Labs on 9/5/18.
//  Copyright © 2018 ARXT Labs. All rights reserved.
//

import UIKit
import Material

class UDMyOrdersViewController: UIViewController {
    @IBOutlet weak var toolBar: Toolbar!
    @IBOutlet weak var tableView: UITableView!
    @IBOutlet weak var noDataLabel: UILabel!
    fileprivate var backButton: IconButton!
    var myJobsArray = NSArray()
    let refreshControl = UIRefreshControl()
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
    
    override func viewWillAppear(_ animated: Bool) {
        getMyJobs()
    }
    
    func loadInitialData() {
        let data = UserDefaults.standard.object(forKey:"userInfo") as! Data
        userInfoDictionary = (NSKeyedUnarchiver.unarchiveObject(with: data) as! NSMutableDictionary?)!
        prepareBackButton()
        prepareToolbar()
        self.tableView.rowHeight = UITableView.automaticDimension
        self.tableView.estimatedRowHeight = 43
        self.tableView.tableFooterView = UIView()
        refreshControl.addTarget(self, action: #selector(didPullToRefresh), for: .valueChanged)
        self.tableView.addSubview(refreshControl)
        ConstantTools.sharedConstantTool.showsMRIndicatorView(self.view,text: "fetching your job details")
    }
    
    @objc func didPullToRefresh() {
        getMyJobs()
    }
    
    func getMyJobs() {
        let merchantId = userInfoDictionary.object(forKey: "merchantid") as? Int ?? 0
        let userId = userInfoDictionary.object(forKey: "carrierid") as? Int ?? 0
        OrdersModel.getMyOrdersDetails(acceptedby: userId, merchantId: merchantId) { connectionResult in
            DispatchQueue.main.async(execute: {() -> Void in
                ConstantTools.sharedConstantTool.hideMRIndicatorView()
                self.refreshControl.endRefreshing()
                switch connectionResult {
                case .success(let data):
                    self.myJobsArray = data
                    self.noDataLabel.isHidden = true
                    self.tableView.isHidden = false
                    self.tableView.reloadData()
                case .failure(let error):
                    self.noDataLabel.isHidden = false
                    self.tableView.isHidden = true
                    self.view.makeToast(error, position: .top)
                }
            })
        }
    }
}

// MARK:- ToolBar
extension UDMyOrdersViewController {
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

// MARK:- UITableViewDataSource
extension UDMyOrdersViewController: UITableViewDataSource, UITableViewDelegate {
    internal func tableView(_ tableView: UITableView, numberOfRowsInSection section: Int) -> Int {
        return myJobsArray.count
    }
    
    internal func tableView(_ tableView: UITableView, cellForRowAt indexPath: IndexPath) -> UITableViewCell {
        let cell = tableView.dequeueReusableCell(withIdentifier: "myJobCell", for: indexPath) as! UDMyJobTableViewCell
        let myJobDict:NSDictionary = myJobsArray[indexPath.row] as! NSDictionary
        let jobId = myJobDict.object(forKey: "orderid") as? Int ?? 0
        let jobTitle = myJobDict.object(forKey: "ordertitle") as? String ?? ""
        let jobDescribtion = myJobDict.object(forKey: "orderdetails") as? String ?? ""
        cell.title.text = "Job Id #: \(jobId) and Title: \(jobTitle)"
        cell.subTitle.text = jobDescribtion
        return cell
    }
    
    internal func tableView(_ tableView: UITableView, didSelectRowAt indexPath: IndexPath) {
        let myJobDict:NSDictionary = myJobsArray[indexPath.row] as! NSDictionary
        let storyboard = UIStoryboard(name: "iPhoneStoryboard", bundle: nil)
        let viewController = storyboard.instantiateViewController(withIdentifier: "UDMyJobDetailsViewController") as! UDMyJobDetailsViewController
        viewController.myJobDict = myJobDict
        self.navigationController?.pushViewController(viewController, animated: true)
    }
}
