//
//  UDSignUpMobileViewController.swift
//  UDeli
//
//  Created by ARXT Labs on 9/24/18.
//  Copyright © 2018 ARXT Labs. All rights reserved.
//

import UIKit

class UDCountryCodeViewController: UIViewController {
    @IBOutlet weak var tableView: UITableView!
    @IBOutlet weak var noCountryLbl: UILabel!
    var delegate: UDCustomViewControllerDelegates?
    var countryArray = NSArray()
    var filterCountryArr = NSArray()
    override func viewDidLoad() {
        super.viewDidLoad()
        loadInitialData()
    }

    // MARK:- View Lifecycle
    override func didReceiveMemoryWarning() {
        super.didReceiveMemoryWarning()
    }
    
    func loadInitialData() {
        noCountryLbl.isHidden = true
        noCountryLbl.text = "No country found"
        tableView.estimatedRowHeight = 50
        tableView.tableFooterView = UIView()
        tableView.separatorInset = UIEdgeInsets.zero
        countryArray = countryArray.countries()
        filterCountryArr = countryArray
    }
    
    func noCountryMessageShown() {
        noCountryLbl.isHidden = true
        if filterCountryArr.count == 0 {
            noCountryLbl.isHidden = false
        }
        self.tableView.reloadData()
    }
    
    @IBAction func dismissView(_ sender: Any) {
        self.dismiss(animated: true, completion: nil)
    }
}

//MARK:- UITableViewDataSource
extension UDCountryCodeViewController: UITableViewDataSource {
    internal func tableView(_ tableView: UITableView, numberOfRowsInSection section: Int) -> Int {
        return filterCountryArr.count
    }
    
    internal func tableView(_ tableView: UITableView, cellForRowAt indexPath: IndexPath) -> UITableViewCell {
        let cell = tableView.dequeueReusableCell(withIdentifier: "countryCell", for: indexPath) as! UDCountryTableViewCell
        let tempDict = filterCountryArr[indexPath.row] as? NSDictionary ?? [:]
        cell.countryName.text = "\(tempDict.object(forKey: "name") ?? "") (\(tempDict.object(forKey: "dial_code") ?? ""))"
        let imagePath = "CountryPicker.bundle/\(tempDict.object(forKey: "code") ?? "").png"
        cell.flagImg.image = UIImage(named: imagePath)
        return cell
    }
}

//MARK:- UITableViewDelegate
extension UDCountryCodeViewController:UITableViewDelegate {
    internal func tableView(_ tableView: UITableView, didSelectRowAt indexPath: IndexPath) {
        let tempDict = filterCountryArr[indexPath.row] as? NSDictionary ?? [:]
        delegate?.countryCodeSelect!(countryData: tempDict)
        self.dismiss(animated: true, completion: nil)
    }
}

//MARK:- UISearchBarDelegate
extension UDCountryCodeViewController: UISearchBarDelegate {
    func searchBarSearchButtonClicked(_ searchBar: UISearchBar) {
        searchBar.resignFirstResponder()
    }
    
    func searchBar(_ searchBar: UISearchBar, textDidChange searchText: String) {
        if searchText.count == 0 {
            filterCountryArr = countryArray
        } else {
            let searchPredit = NSPredicate(format: "(name contains[c] %@) || (dial_code contains[c] %@) || (code contains[c] %@)",searchText,searchText,searchText)
            filterCountryArr = countryArray.filtered(using: searchPredit) as NSArray
        }
        self.noCountryMessageShown()
    }
    
    func searchBarCancelButtonClicked(_ searchBar: UISearchBar) {
        searchBar.text = ""
        searchBar.resignFirstResponder()
        filterCountryArr = countryArray
        self.noCountryMessageShown()
    }
}
