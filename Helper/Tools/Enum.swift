//
//  Enum.swift
//  oogioogi
//
//  Created by ARXT Labs on 7/25/18.
//  Copyright © 2018 ARXT Labs. All rights reserved.
//

import Foundation

enum ConnectionResultAsDictionary {
    case success(NSDictionary)
    case failure(String)
}

enum ConnectionResultAsArray {
    case success(NSArray)
    case failure(String)
}

enum NotificationType: Int {
    case None = 0
    case ByText = 1
    case ByEmail = 2
}
var NotificationTypeId = NotificationType.None

enum OrderStatusType: Int {
    case None = 0
    case Accepted = 1
    case InProgress = 2
    case Delivered = 3
}
var OrderStatusTypeTypeId = OrderStatusType.None
