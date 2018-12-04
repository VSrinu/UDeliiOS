//
//  UDCompletedJobDetailsViewController.swift
//  oogioogi
//
//  Created by ARXT Labs on 11/16/18.
//  Copyright © 2018 ARXT Labs. All rights reserved.
//

import UIKit
import Material
import MapKit

class UDCompletedJobDetailsViewController: UIViewController {
    @IBOutlet weak var toolBar: Toolbar!
    @IBOutlet weak var tableView: UITableView!
    fileprivate var backButton: IconButton!
    var myJobDict = NSDictionary()
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
        prepareBackButton()
        prepareToolbar()
        self.tableView.rowHeight = UITableView.automaticDimension
        self.tableView.estimatedRowHeight = 43
        self.tableView.tableFooterView = UIView()
        self.tableView.reloadData()
    }
    
    // MARK:- Button Actions
    @objc
    fileprivate func navigateBack(button: UIButton) {
        self.navigationController!.popViewController(animated: true)
    }
}

// MARK:- ToolBar
extension UDCompletedJobDetailsViewController {
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
}

// MARK:- UITableViewDataSource
extension UDCompletedJobDetailsViewController: UITableViewDataSource, UITableViewDelegate {
    internal func numberOfSections(in tableView: UITableView) -> Int {
        return 3
    }
    
    internal func tableView(_ tableView: UITableView, numberOfRowsInSection section: Int) -> Int {
        return 1
    }
    
    internal func tableView(_ tableView: UITableView, heightForHeaderInSection section: Int) -> CGFloat {
        return 0.0001
    }
    
    internal func tableView(_ tableView: UITableView, heightForFooterInSection section: Int) -> CGFloat {
        return 0.0001
    }
    
    internal func tableView(_ tableView: UITableView, cellForRowAt indexPath: IndexPath) -> UITableViewCell {
        if indexPath.section == 0 {
            let cell = tableView.dequeueReusableCell(withIdentifier: "jobDetailsCell", for: indexPath) as! UDJobDetailsTableViewCell
            cell.pulseAnimation = .none
            let customerName = myJobDict.object(forKey: "customername") as? String ?? ""
            let city = myJobDict.object(forKey: "city") as? String ?? ""
            let preferreddeliverytime = myJobDict.object(forKey: "preferreddeliverytime") as? Date ?? Date()
            let deliverDate = ConstantTools.sharedConstantTool.dayFormate(date: preferreddeliverytime)
            let deliverMonth = ConstantTools.sharedConstantTool.mothFormate(date: preferreddeliverytime)
            let time = ConstantTools.sharedConstantTool.timeFormate(date: preferreddeliverytime)
            let address = myJobDict.object(forKey: "address") as? String ?? ""
            let state = myJobDict.object(forKey: "state") as? String ?? ""
            let zip = myJobDict.object(forKey: "zip") as? String ?? ""
            cell.jobId.text = "Delivered to \(customerName) at\n\(address), \(city), \(state), \(zip)\n at \(deliverMonth) \(deliverDate) \(time)"
            let orderId = myJobDict.object(forKey: "orderid") as? Int ?? 0
            let orderTitle = myJobDict.object(forKey: "ordertitle") as? String ?? ""
            cell.jobTitle.text = "\(orderId): \(orderTitle)"
            cell.jobDetails.text = "\(myJobDict.object(forKey: "orderdetails") as? String ?? "")"
            cell.jobAcceptBtn.isHidden = true
            cell.jobDismissBtn.isHidden = true
            return cell
        } else if indexPath.section == 1 {
            let cell = tableView.dequeueReusableCell(withIdentifier: "mapCell", for: indexPath) as! UDJobDetailsTableViewCell
            cell.pulseAnimation = .none
            let city = myJobDict.object(forKey: "city") as? String ?? ""
            let state = myJobDict.object(forKey: "state") as? String ?? ""
            let zip = myJobDict.object(forKey: "zip") as? String ?? ""
            let fullAddress = "\(city),\(state),\(zip)"
            ConstantTools.sharedConstantTool.getCoordinate(address: fullAddress, mapView: cell.mapView,customerName:fullAddress)
            cell.directionBtn.isHidden = true
            return cell
        } else {
            let cell = tableView.dequeueReusableCell(withIdentifier: "jobSectionCell", for: indexPath) as! UDJobDetailsTableViewCell
            cell.pulseAnimation = .none
            cell.packageCountLabel.text = "# of Packages: \(myJobDict.object(forKey: "numberofbags") as? Int ?? 0)"
            let perishable = myJobDict.object(forKey: "perishable") as? Bool ?? false
            let fragile = myJobDict.object(forKey: "fragile") as? Bool ?? false
            var isperishable = String()
            var isfragile = String()
            perishable == true ? (isperishable = "YES") : (isperishable = "NO")
            fragile == true ? (isfragile = "YES") : (isfragile = "NO")
            cell.fragileLabel.text = "Fragile: \(isfragile)"
            cell.perishablesLabel.text = "Pershables: \(isperishable)"
            cell.distanceLabel.text = "Weight: \(myJobDict.object(forKey: "totalweight") as? Int ?? 0) lbs"
            return cell
        }
    }
}

