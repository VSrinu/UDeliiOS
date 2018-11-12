//
//  ForgotPasswordModel.swift
//  UDeli
//
//  Created by ARXT Labs on 8/6/18.
//  Copyright © 2018 ARXT Labs. All rights reserved.
//

import Foundation

struct ForgotPasswordModel {
    // Get ForgetPassword
    static func forgotPassword(mobileNumber: String, newPassword:String, completion: @escaping (ConnectionResultAsDictionary) -> ()) {
        Internet.isAvailable { (status, message) in
            if status {
                // Check Mobile Number and Password
                let predicate = NSPredicate(format: "phonenumber = %@", argumentArray: [mobileNumber])
                tCarrier.read(with: predicate) { (result, error) in
                    if let err = error {
                        completion(.failure(err.localizedDescription))
                    } else if let items = result?.items {
                        let response = items as NSArray
                        if response.count == 0 {
                            completion(.failure("Please check your mobile Number or Password"))
                        } else {
                            // update password
                            let responseDict = response.firstObject as? NSDictionary ?? [:]
                            let tableId = responseDict.object(forKey: "id") as? String ?? ""
                            let itemDict: NSDictionary = ["phonenumber": mobileNumber, "id": tableId]
                            if let newItem = itemDict.mutableCopy() as? NSMutableDictionary {
                                newItem["plaintextpass"] = newPassword
                                tCarrier.update(newItem as [NSObject: AnyObject], completion: { (result, error) -> Void in
                                    if let err = error {
                                        completion(.failure(err.localizedDescription))
                                    } else if let item = result {
                                        completion(.success(item as NSDictionary))
                                    }
                                })
                            }
                        }
                    }
                }
            } else {
                completion(.failure(message))
            }
        }
    }
}
