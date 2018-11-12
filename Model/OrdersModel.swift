//
//  OrdersModel.swift
//  UDeli
//
//  Created by ARXT Labs on 8/22/18.
//  Copyright © 2018 ARXT Labs. All rights reserved.
//

import Foundation

struct OrdersModel {
    // Get Orders List
    static func getOrdersDetails(acceptedby: Int, merchantId:Int, completion: @escaping (ConnectionResultAsArray) -> ()) {
        Internet.isAvailable { (status, message) in
            if status {
                let merchantPredicate =  NSPredicate(format: "merchantid == \(merchantId)")
                let listPredicate = NSPredicate(format: "status = \(OrderStatusType.None.rawValue)")
                let acceptedPredicate = NSPredicate(format: "acceptedby = nil")
                let predicate = NSCompoundPredicate(andPredicateWithSubpredicates: [merchantPredicate,listPredicate,acceptedPredicate])
                tOrders.read(with: predicate) { (result, error) in
                    if let err = error {
                        completion(.failure(err.localizedDescription))
                    } else if let items = result?.items {
                        let response = items as NSArray
                        response.count != 0 ? completion(.success(response)) : completion(.failure("No Orders to deliver."))
                    }
                }
            } else {
                completion(.failure(message))
            }
        }
    }
    
    // Update order status
    static func updateOrderStatus(acceptedby: Int, oderStatus: String, orderId:String, completion: @escaping (ConnectionResultAsDictionary) -> ()) {
        Internet.isAvailable { (status, message) in
            if status {
                let itemDict: NSDictionary = ["id": orderId]
                if let newItem = itemDict.mutableCopy() as? NSMutableDictionary {
                    newItem["acceptedby"] = acceptedby
                    newItem["status"] = oderStatus
                    tOrders.update(newItem as [NSObject: AnyObject], completion: { (result, error) -> Void in
                        if let err = error {
                            completion(.failure(err.localizedDescription))
                        } else if let item = result {
                            completion(.success(item as NSDictionary))
                        }
                    })
                }
            } else {
                completion(.failure(message))
            }
        }
    }
    
    // Get MyOrders
    static func getMyOrdersDetails(acceptedby: Int, merchantId:Int, completion: @escaping (ConnectionResultAsArray) -> ()) {
        Internet.isAvailable { (status, message) in
            if status {
                let merchantPredicate =  NSPredicate(format: "merchantid == \(merchantId)")
                let listPredicate = NSPredicate(format: "status = \(OrderStatusType.Accepted.rawValue) || status = \(OrderStatusType.InProgress.rawValue)")
                let acceptedPredicate = NSPredicate(format: "acceptedby = \(acceptedby)")
                let predicate = NSCompoundPredicate(andPredicateWithSubpredicates: [merchantPredicate,listPredicate,acceptedPredicate])
                tOrders.read(with: predicate) { (result, error) in
                    if let err = error {
                        completion(.failure(err.localizedDescription))
                    } else if let items = result?.items {
                        let response = items as NSArray
                        response.count != 0 ? completion(.success(response)) : completion(.failure("No Orders to deliver."))
                    }
                }
            } else {
                completion(.failure(message))
            }
        }
    }
}
