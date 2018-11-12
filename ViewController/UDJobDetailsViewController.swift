//
//  UDJobDetailsViewController.swift
//  UDeli
//
//  Created by ARXT Labs on 7/4/18.
//  Copyright © 2018 ARXT Labs. All rights reserved.
//

import UIKit
import Material
import MapKit

class UDJobDetailsViewController: UIViewController {
    @IBOutlet weak var toolBar: Toolbar!
    @IBOutlet weak var tableView: UITableView!
    fileprivate var backButton: IconButton!
    var jobDict = NSDictionary()
    override func viewDidLoad() {
        super.viewDidLoad()
        self.loadInitialData()
    }

    // MARK:- View Lifecycle
    override func didReceiveMemoryWarning() {
        super.didReceiveMemoryWarning()
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
    
    @objc
    fileprivate func tapToAcceptJobs(button: UIButton) {
        let orderId = jobDict.object(forKey: "id") as? String ?? ""
        let acceptedby = userInfoDictionary.object(forKey: "carrierid") as? Int ?? 0
        ConstantTools.sharedConstantTool.showsMRIndicatorView(self.view)
        OrdersModel.updateOrderStatus(acceptedby: acceptedby, oderStatus: String(OrderStatusType.Accepted.rawValue), orderId: orderId) { connectionResult in
            DispatchQueue.main.async(execute: {() -> Void in
                ConstantTools.sharedConstantTool.hideMRIndicatorView()
                switch connectionResult {
                case .success(let data):
                    print(data)
                    self.getAlert()
                case .failure(let error):
                    self.view.makeToast(error, position: .top)
                }
            })
        }
    }
    
    func getAlert() {
        self.present(UIAlertController.alertWithTitle(title: "Job Accepted", message: "We have accepted your. It will update in my orderList", buttonTitle: "OK", handler: { action in self.updateLandingPage()}), animated: true)
    }
    
    func updateLandingPage() {
        self.navigationController!.popViewController(animated: true)
    }
    
    @objc
    fileprivate func tapToDismissPage(button: UIButton) {
        self.navigationController!.popViewController(animated: true)
    }
    
    @objc
    fileprivate func tapToDirection(button: UIButton) {
        let city = jobDict.object(forKey: "city") as? String ?? ""
        let state = jobDict.object(forKey: "state") as? String ?? ""
        let zip = jobDict.object(forKey: "zip") as? String ?? ""
        let fullAddress = "\(city),\(state),\(zip)"
        let geocoder = CLGeocoder()
        geocoder.geocodeAddressString(fullAddress) { (placemarks, error) in
            if error == nil {
                if let placemark = placemarks?[0] {
                    let location = placemark.location!
                    if (UIApplication.shared.canOpenURL(URL(string:"comgooglemaps://")!)) {
                        UIApplication.shared.open(URL(string:
                            "comgooglemaps://?saddr=&daddr=\(location.coordinate.latitude),\(location.coordinate.longitude)&views=transit")!, options: [:], completionHandler: nil)
                    } else {
                        UIApplication.shared.open(URL(string:
                            "https://www.google.co.in/maps/dir/?saddr=&daddr=\(location.coordinate.latitude),\(location.coordinate.longitude)&views=transit")!, options: [:], completionHandler: nil)
                    }
                    return
                }
            }
        }
    }
}

// MARK:- ToolBar
extension UDJobDetailsViewController {
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
extension UDJobDetailsViewController: UITableViewDataSource, UITableViewDelegate {
    internal func numberOfSections(in tableView: UITableView) -> Int {
        return 3
    }
    
    internal func tableView(_ tableView: UITableView, numberOfRowsInSection section: Int) -> Int {
        return 1
    }
    
    internal func tableView(_ tableView: UITableView, heightForHeaderInSection section: Int) -> CGFloat {
        return 5
    }
    
    internal func tableView(_ tableView: UITableView, heightForFooterInSection section: Int) -> CGFloat {
        return 0.0001
    }
    
    internal func tableView(_ tableView: UITableView, cellForRowAt indexPath: IndexPath) -> UITableViewCell {
        if indexPath.section == 0 {
            let cell = tableView.dequeueReusableCell(withIdentifier: "jobDetailsCell", for: indexPath) as! UDJobDetailsTableViewCell
            cell.pulseAnimation = .none
            cell.jobId.text = "Delivery Job#: \(jobDict.object(forKey: "orderid") as? Int ?? 0)"
            cell.jobTitle.text = "Job Title: \(jobDict.object(forKey: "ordertitle") as? String ?? "")"
            cell.jobDetails.text = "\(jobDict.object(forKey: "orderdetails") as? String ?? "")"
            cell.jobAcceptBtn.addTarget(self, action: #selector(tapToAcceptJobs(button:)), for: .touchUpInside)
            cell.jobDismissBtn.addTarget(self, action: #selector(tapToDismissPage(button:)), for: .touchUpInside)
            return cell
        } else if indexPath.section == 1 {
            let cell = tableView.dequeueReusableCell(withIdentifier: "mapCell", for: indexPath) as! UDJobDetailsTableViewCell
            cell.pulseAnimation = .none
            let city = jobDict.object(forKey: "city") as? String ?? ""
            let state = jobDict.object(forKey: "state") as? String ?? ""
            let zip = jobDict.object(forKey: "zip") as? String ?? ""
            let fullAddress = "\(city),\(state),\(zip)"
            ConstantTools.sharedConstantTool.getCoordinate(address: fullAddress, mapView: cell.mapView,customerName:fullAddress)
            cell.directionBtn.addTarget(self, action: #selector(tapToDirection(button:)), for: .touchUpInside)
            return cell
        } else {
            let cell = tableView.dequeueReusableCell(withIdentifier: "jobSectionCell", for: indexPath) as! UDJobDetailsTableViewCell
            cell.pulseAnimation = .none
            cell.packageCountLabel.text = "Number of Packages: \(jobDict.object(forKey: "numberofbags") as? Int ?? 0)"
            let perishable = jobDict.object(forKey: "perishable") as? Bool ?? false
            let fragile = jobDict.object(forKey: "fragile") as? Bool ?? false
            var isperishable = String()
            var isfragile = String()
            perishable == true ? (isperishable = "YES") : (isperishable = "NO")
            fragile == true ? (isfragile = "YES") : (isfragile = "NO")
            cell.fragileLabel.text = "Is Fragile: \(isfragile)"
            cell.perishablesLabel.text = "Is Pershables: \(isperishable)"
            let preferreddeliverytime = jobDict.object(forKey: "preferreddeliverytime") as? Date ?? Date()
            let deliverDate = ConstantTools.sharedConstantTool.dateFormate(date: preferreddeliverytime)
            let time = ConstantTools.sharedConstantTool.timeFormate(date: preferreddeliverytime)
            cell.deliveryDateLabel.text = "Deliver by Date and Time: \(deliverDate) \(time)"
            let city = jobDict.object(forKey: "city") as? String ?? ""
            let state = jobDict.object(forKey: "state") as? String ?? ""
            let zip = jobDict.object(forKey: "zip") as? String ?? ""
            let fullAddress = "\(city),\(state),\(zip)"
            cell.addressLabel.text = fullAddress
            cell.distanceLabel.text = "Distance Frome Store: \(jobDict.object(forKey: "storetocustlocation") as? Int ?? 0)KM"
            return cell
        }
    }
}
