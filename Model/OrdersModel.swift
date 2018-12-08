//
//  OrdersModel.swift
//  oogioogi
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
                let acceptedPredicate = NSPredicate(format: "carrierid = \(acceptedby)")
                let predicate = NSCompoundPredicate(andPredicateWithSubpredicates: [merchantPredicate,acceptedPredicate])
                tOrderToCarriers.read(with: predicate) { (result, error) in
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
    static func acceptOrderStatus(acceptedby: Int, oderStatus: String, orderId:String, checkOrderId:Int, completion: @escaping (ConnectionResultAsDictionary) -> ()) {
        Internet.isAvailable { (status, message) in
            if status {
                let statusPredicate =  NSPredicate(format: "status == \(OrderStatusType.Accepted.rawValue)")
                let orderPredicate = NSPredicate(format: "orderid == \(checkOrderId)")
                let predicate = NSCompoundPredicate(andPredicateWithSubpredicates: [statusPredicate,orderPredicate])
                tOrders.read(with: predicate) { (result, error) in
                    if let err = error {
                        completion(.failure(err.localizedDescription))
                    } else if let items = result?.items {
                        let response = items as NSArray
                        if response.count == 0 {
                            let itemDict: NSDictionary = ["id": orderId]
                            if let newItem = itemDict.mutableCopy() as? NSMutableDictionary {
                                newItem["acceptedby"] = acceptedby
                                newItem["status"] = oderStatus
                                if oderStatus == String(OrderStatusType.Accepted.rawValue) {
                                    newItem["accepteddatetime"] = Date()
                                } else if oderStatus == String(OrderStatusType.Delivered.rawValue) {
                                    newItem["delivereddatetime"] = Date()
                                }
                                tOrders.update(newItem as [NSObject: AnyObject], completion: { (result, error) -> Void in
                                    if let err = error {
                                        completion(.failure(err.localizedDescription))
                                    } else if let item = result {
                                        completion(.success(item as NSDictionary))
                                    }
                                })
                            }
                        } else {
                            completion(.failure("This order has been accepted by another carrier. Please find another order"))
                        }
                    } else {
                        completion(.failure("This order has been accepted by another carrier. Please find another order"))
                    }
                }
            } else {
                completion(.failure(message))
            }
        }
    }
    
    static func updateOrderStatus(acceptedby: Int, oderStatus: String, orderId:String, completion: @escaping (ConnectionResultAsDictionary) -> ()) {
        Internet.isAvailable { (status, message) in
            if status {
                let itemDict: NSDictionary = ["id": orderId]
                if let newItem = itemDict.mutableCopy() as? NSMutableDictionary {
                    newItem["acceptedby"] = acceptedby
                    newItem["status"] = oderStatus
                    if oderStatus == String(OrderStatusType.Accepted.rawValue) {
                        newItem["accepteddatetime"] = Date()
                    } else if oderStatus == String(OrderStatusType.Delivered.rawValue) {
                        newItem["delivereddatetime"] = Date()
                    }
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
    
    // Get My Completed Orders
    static func getMyCompletedOrdersDetails(acceptedby: Int, merchantId:Int, completion: @escaping (ConnectionResultAsArray) -> ()) {
        Internet.isAvailable { (status, message) in
            if status {
                let merchantPredicate =  NSPredicate(format: "merchantid == \(merchantId)")
                let listPredicate = NSPredicate(format: "status = \(OrderStatusType.Delivered.rawValue) || status = \(OrderStatusType.InProgress.rawValue)")
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
    
    // Get Single Orders
    static func getSingleOrdersDetails(orderid: Int, completion: @escaping (ConnectionResultAsDictionary) -> ()) {
        Internet.isAvailable { (status, message) in
            if status {
                let merchantPredicate =  NSPredicate(format: "orderid == \(orderid)")
                tOrders.read(with: merchantPredicate) { (result, error) in
                    if let err = error {
                        completion(.failure(err.localizedDescription))
                    } else if let items = result?.items {
                        let response = items as NSArray
                        let orders = response.firstObject as? NSDictionary ?? [:]
                        completion(.success(orders))
                    }
                }
            } else {
                completion(.failure(message))
            }
        }
    }
}
