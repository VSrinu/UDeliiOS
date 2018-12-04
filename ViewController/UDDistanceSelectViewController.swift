//
//  UDDistanceSelectViewController.swift
//  oogioogi
//
//  Created by ARXT Labs on 8/8/18.
//  Copyright © 2018 ARXT Labs. All rights reserved.
//

import UIKit

class UDDistanceSelectViewController: UIViewController {
    @IBOutlet weak var tableView: UITableView!
    var milesArray = NSArray()
    var pageTitle = String()
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
         self.milesArray = [["value": 10, "title": "10 mi"], ["value": 20, "title": "20 mi"], ["value": 30, "title": "30 mi"], ["value": 40, "title": "40 mi"], ["value": 50, "title": "50 mi"], ["value": 60, "title": "60 mi"], ["value": 70, "title": "70 mi"], ["value": 80, "title": "80 mi"], ["value": 90, "title": "90 mi"], ["value": 100, "title": "100 mi"]]
        self.tableView.rowHeight = UITableView.automaticDimension
        self.tableView.estimatedRowHeight = 43
        self.tableView.tableFooterView = UIView()
        self.tableView.reloadData()
    }
    
    func updateValue(milesSelection:Int) {
        pageTitle == "store" ? updateStoreDistance(milesSelection:milesSelection) : updateHomeDistance(milesSelection:milesSelection)
    }
    
    func updateStoreDistance(milesSelection:Int) {
        ConstantTools.sharedConstantTool.showsMRIndicatorView(self.view,text: "updating your settings")
        ProfileUpdateModel.updateDistanceFromStore(distancefromstore: milesSelection, userId: userInfoDictionary.object(forKey: "id") as? String ?? "") { connectionResult in
            DispatchQueue.main.async(execute: {() -> Void in
                ConstantTools.sharedConstantTool.hideMRIndicatorView()
                switch connectionResult {
                case .success(let data):
                    userInfoDictionary.setValuesForKeys(data as! [String : Any])
                    let userData = NSKeyedArchiver.archivedData(withRootObject: userInfoDictionary)
                    UserDefaults.standard.set(userData, forKey: "userInfo")
                    self.navigationController!.popViewController(animated: true)
                case .failure(let error):
                    self.view.makeToast(error, position: .top)
                }
            })
            
        }
    }
    
    func updateHomeDistance(milesSelection:Int) {
        ConstantTools.sharedConstantTool.showsMRIndicatorView(self.view,text: "updating your settings")
        ProfileUpdateModel.updateDistanceFromHome(distancefromhome: milesSelection, userId: userInfoDictionary.object(forKey: "id") as? String ?? "") { connectionResult in
            DispatchQueue.main.async(execute: {() -> Void in
                ConstantTools.sharedConstantTool.hideMRIndicatorView()
                switch connectionResult {
                case .success(let data):
                    userInfoDictionary.setValuesForKeys(data as! [String : Any])
                    let userData = NSKeyedArchiver.archivedData(withRootObject: userInfoDictionary)
                    UserDefaults.standard.set(userData, forKey: "userInfo")
                    self.navigationController!.popViewController(animated: true)
                case .failure(let error):
                    self.view.makeToast(error, position: .top)
                }
            })
            
        }
    }
    
    @IBAction func tapToNavigateBack(_ sender: Any) {
        self.navigationController!.popViewController(animated: true)
    }
}

// MARK:- UITableViewDataSource
extension UDDistanceSelectViewController: UITableViewDataSource, UITableViewDelegate {
    internal func tableView(_ tableView: UITableView, numberOfRowsInSection section: Int) -> Int {
        return milesArray.count
    }
    
    internal func tableView(_ tableView: UITableView, cellForRowAt indexPath: IndexPath) -> UITableViewCell {
        let cell = tableView.dequeueReusableCell(withIdentifier: "tableViewCell", for: indexPath) as! UDTableViewCell
        let milesDict:NSDictionary = milesArray[indexPath.row] as! NSDictionary
        let milesTitle = milesDict.object(forKey: "title") as? String ?? ""
        cell.label.text = milesTitle
        cell.accessoryType = .none
        return cell
    }
    
    internal func tableView(_ tableView: UITableView, didSelectRowAt indexPath: IndexPath) {
        tableView.cellForRow(at: indexPath as IndexPath)?.accessoryType = .checkmark
        let milesSelectionDict = milesArray[indexPath.row] as! NSDictionary
        let milesvalue = milesSelectionDict.object(forKey: "value") as? Int ?? 0
        updateValue(milesSelection:milesvalue)
    }
    
    internal func tableView(_ tableView: UITableView, didDeselectRowAt indexPath: IndexPath) {
        tableView.cellForRow(at: indexPath as IndexPath)?.accessoryType = .none
    }
}
