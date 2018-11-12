//
//  UDCustomViewControllerDelegates.swift
//  UDeli
//
//  Created by ARXT Labs on 6/28/18.
//  Copyright © 2018 ARXT Labs. All rights reserved.
//

import UIKit

@objc protocol UDCustomViewControllerDelegates {
    @objc optional func NavigateFromPresentViewFunction()
    @objc optional func CustomCellUpdater(notificationType:Int)
    @objc optional func countryCodeSelect(countryData:NSDictionary)
}
