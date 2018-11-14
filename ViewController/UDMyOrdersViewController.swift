//
//  UDMyOrdersViewController.swift
//  UDeli
//
//  Created by ARXT Labs on 9/5/18.
//  Copyright © 2018 ARXT Labs. All rights reserved.
//

import UIKit
import Material
import EnRouteApi

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
        EnRouteWrapper.instance.manager()?.add(self)
        EnRouteWrapper.instance.manager()?.getTaskManager().add(self)
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
        EnRouteWrapper.instance.manager()?.refresh()
        getMyJobs()
    }
    
    func taskListChanged() {
        tableView.reloadData()
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
        return (EnRouteWrapper.instance.manager()?.getTaskManager().getTasks().count())!
    }
    
    internal func tableView(_ tableView: UITableView, heightForHeaderInSection section: Int) -> CGFloat {
        if section == 0 {
            return 6
        }
        return 0.0001
    }
    
    internal func tableView(_ tableView: UITableView, heightForFooterInSection section: Int) -> CGFloat {
        return 0.0001
    }
    
    internal func tableView(_ tableView: UITableView, cellForRowAt indexPath: IndexPath) -> UITableViewCell {
        let cell = tableView.dequeueReusableCell(withIdentifier: "myJobCell", for: indexPath) as! UDLandingCell
        let task:GlyTask = (EnRouteWrapper.instance.manager()?.getTaskManager().getTasks().object(at: indexPath.row))!
        let predicate = NSPredicate(format: "glympsetaskid == \(task.getId())")
        let tempArray = myJobsArray.filtered(using: predicate) as NSArray
        let myJobDict = tempArray.firstObject as? NSDictionary ?? [:]
        let orderId = myJobDict.object(forKey: "orderid") as? Int ?? 0
        cell.jobIdLabel.text = "\(orderId)"
        let preferreddeliverytime = myJobDict.object(forKey: "preferreddeliverytime") as? Date ?? Date()
        let deliverDate = ConstantTools.sharedConstantTool.dayFormate(date: preferreddeliverytime)
        cell.deliveryDate.text = deliverDate
        let deliverMonth = ConstantTools.sharedConstantTool.mothFormate(date: preferreddeliverytime)
        cell.deliveryMonth.text = deliverMonth
        let time = ConstantTools.sharedConstantTool.timeFormate(date: preferreddeliverytime)
        cell.deliveryTime.text = time
        let customerName = myJobDict.object(forKey: "customername") as? String ?? ""
        let city = myJobDict.object(forKey: "city") as? String ?? ""
        cell.jobDetails.text = "Deliver to \(customerName) at \(city)"
        cell.distanceFromStore.text = "From Store: \(myJobDict.object(forKey: "storetocustlocation") as? Double ?? 0.0) Miles"
        cell.distanceFromeAddress.text = "From your Address: \(myJobDict.object(forKey: "carriertocustlocation") as? Double ?? 0.0) Miles"
        cell.activeCarriers.text = "# of Active Carriers: \(myJobDict.object(forKey: "carriercount") as? Int ?? 0)"
        return cell
    }
    
    internal func tableView(_ tableView: UITableView, didSelectRowAt indexPath: IndexPath) {
        let task:GlyTask = (EnRouteWrapper.instance.manager()?.getTaskManager().getTasks().object(at: indexPath.row))!
        let predicate = NSPredicate(format: "glympsetaskid == \(task.getId())")
        let tempArray = myJobsArray.filtered(using: predicate) as NSArray
        let myJobDict = tempArray.firstObject as? NSDictionary ?? [:]
        let storyboard = UIStoryboard(name: "iPhoneStoryboard", bundle: nil)
        let viewController = storyboard.instantiateViewController(withIdentifier: "UDMyJobDetailsViewController") as! UDMyJobDetailsViewController
        viewController.myJobDict = myJobDict
        self.navigationController?.pushViewController(viewController, animated: true)
    }
}

// MARK:- GlyListener
extension UDMyOrdersViewController: GlyListener {
    func eventsOccurred(_ source: GlySource!, listener: Int32, events: Int32, param1: GlyCommon!, param2: GlyCommon!) {
        if GlyEnRouteEvents.listener_ENROUTE_MANAGER() == listener {
            if 0 != ( events & GlyEnRouteEvents.enroute_MANAGER_LOGGED_OUT() ) {
                print("not giympse details")
            }
        }
        else if GlyEnRouteEvents.listener_TASKS() == listener {
            if 0 != ( events & GlyEnRouteEvents.tasks_TASK_LIST_CHANGED() ) {
                taskListChanged()
            }
            if 0 != ( events & GlyEnRouteEvents.tasks_TASK_STARTED() ) {
                taskListChanged()
            }
            if 0 != ( events & GlyEnRouteEvents.tasks_TASK_START_FAILED() ) {
                taskListChanged()
            }
            if 0 != ( events & GlyEnRouteEvents.tasks_OPERATION_COMPLETED() ) {
                taskListChanged()
            }
            if 0 != ( events & GlyEnRouteEvents.tasks_OPERATION_COMPLETION_FAILED() ) {
                taskListChanged()
            }
        }
    }
}
