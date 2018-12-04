//
//  TableViewCell.swift
//  oogioogi
//
//  Created by ARXT Labs on 6/29/18.
//  Copyright © 2018 ARXT Labs. All rights reserved.
//

import UIKit
import Material
import FoldingCell
import MapKit

class UDProfileTableViewCell: TableViewCell {
    var customDelegate: UDCustomViewControllerDelegates?
    @IBOutlet weak var titleLabel: UILabel!
    @IBOutlet weak var detailsLabel: UILabel!
    @IBOutlet weak var mobileRadioBtn: CheckButton!
    @IBOutlet weak var emailRadioBtn: CheckButton!
    @IBOutlet weak var storeDistanceBtn: RaisedButton!
    var notificationType = Int()
    
    @IBAction func tapToSendByText(_ sender: Any) {
        let buttonStatus:Bool = (sender as AnyObject).isSelected
        if buttonStatus {
            notificationType = NotificationType.ByText.rawValue
            emailRadioBtn.isSelected = false
        } else {
            notificationType = NotificationType.None.rawValue
        }
        customDelegate?.CustomCellUpdater!(notificationType:notificationType)
    }
    
    @IBAction func tapToSendByEmail(_ sender: Any) {
        let buttonStatus:Bool = (sender as AnyObject).isSelected
        if buttonStatus {
            notificationType = NotificationType.ByEmail.rawValue
            mobileRadioBtn.isSelected = false
        } else {
            notificationType = NotificationType.None.rawValue
        }
        customDelegate?.CustomCellUpdater!(notificationType:notificationType)
    }
}

class UDEditProfileTableViewCell: TableViewCell {
    @IBOutlet weak var titleLabel: UILabel!
    @IBOutlet weak var textField: UITextField!
}

class UDSettingTableViewCell: TableViewCell {
    @IBOutlet weak var icon: UIImageView!
    @IBOutlet weak var titleLabel: UILabel!
}

class UDJobDetailsTableViewCell: TableViewCell {
    @IBOutlet weak var jobId: UILabel!
    @IBOutlet weak var jobTitle: UILabel!
    @IBOutlet weak var jobDetails: UILabel!
    @IBOutlet weak var jobAcceptBtn: RaisedButton!
    @IBOutlet weak var jobDismissBtn: RaisedButton!
    @IBOutlet weak var mapView: MKMapView!
    @IBOutlet weak var directionBtn: DesignableButton!
    @IBOutlet weak var packageCountLabel: UILabel!
    @IBOutlet weak var fragileLabel: UILabel!
    @IBOutlet weak var perishablesLabel: UILabel!
    @IBOutlet weak var distanceLabel: UILabel!
}

class UDTableViewCell: TableViewCell {
    @IBOutlet weak var label: UILabel!
}

class UDLandingCell: TableViewCell {
    @IBOutlet weak var cellView: UIView!
    @IBOutlet weak var jobIdLabel: UILabel!
    @IBOutlet weak var deliveryTime: UILabel!
    @IBOutlet weak var deliveryMonth: UILabel!
    @IBOutlet weak var deliveryDate: UILabel!
    @IBOutlet weak var jobDetails: UILabel!
    @IBOutlet weak var distanceFromStore: UILabel!
    @IBOutlet weak var distanceFromeAddress: UILabel!
    @IBOutlet weak var activeCarriers: UILabel!
    
    override func awakeFromNib() {
        cellView.layer.cornerRadius = 10
        cellView.layer.masksToBounds = true
        super.awakeFromNib()
    }
}

class UDMyJobTableViewCell: TableViewCell {
    @IBOutlet weak var title: UILabel!
    @IBOutlet weak var subTitle: UILabel!
}

class UDCountryTableViewCell: UITableViewCell {
    @IBOutlet weak var countryName: UILabel!
    @IBOutlet weak var flagImg: UIImageView!
}
