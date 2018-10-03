//
//  SignUpModel.swift
//  UDeli
//
//  Created by ARXT Labs on 6/25/18.
//  Copyright © 2018 ARXT Labs. All rights reserved.
//

import Foundation

struct SignUpModel {
    // Get SignUp
    static func signUp(fName: String, lName: String, phoneNumber: String, password: String, emailId: String, address: String, city: String, state: String, zip: String, userDetails: NSDictionary, devicePlatform: String, deviceToken: String, deviceUuid: String, deviceVersion: String, deviceName: String, deviceModel: String, appVersion : String, completion: @escaping (ConnectionResultAsDictionary) -> ()) {
        Internet.isAvailable { (status, message) in
            if status {
                // Check Mobile Number
                let predicate =  NSPredicate(format: "phonenumber == \(phoneNumber)")
                tCarrier.read(with: predicate) { (result, error) in
                    if let err = error {
                        completion(.failure(err.localizedDescription))
                    } else if let items = result?.items {
                        let response = items as NSArray
                        if response.count != 0 {
                            completion(.failure("This Mobile Number is Already Registered. Please use another Mobile Number to Register"))
                        } else {
                            // Insert user details
                            let itemToInsert = ["firstname": fName, "lastname": lName, "phonenumber": phoneNumber, "plaintextpass": password, "emailid": emailId, "address": address, "city": city, "state": state, "zip": zip, "latitude": userDetails.object(forKey: "latitude") ?? "", "longitude": userDetails.object(forKey: "longitude") ?? "", "deviceplatform": devicePlatform, "devicetoken": deviceToken, "deviceuuid": deviceUuid, "deviceversion": deviceVersion, "devicename": deviceName, "devicemodel": deviceModel, "profilestatus":1, "appversion": appVersion] as [String : Any]
                            tCarrier.insert(itemToInsert) { (result, error) in
                                if let err = error {
                                    completion(.failure(err.localizedDescription))
                                } else if let item = result {
                                    let response = item as NSDictionary
                                    completion(.success(response))
                                }
                            }
                        }
                    }
                }
            } else {
                completion(.failure(message))
            }
        }
    }
    
    // Get check Mobile Number
    static func checkMobileNumber(phoneNumber: String, completion: @escaping (ConnectionResultAsArray) -> ()) {
        Internet.isAvailable { (status, message) in
            if status {
                // Check Mobile Number
                let predicate =  NSPredicate(format: "phonenumber == \(phoneNumber)")
                tCarrier.read(with: predicate) { (result, error) in
                    if let err = error {
                        completion(.failure(err.localizedDescription))
                    } else if let items = result?.items {
                        let response = items as NSArray
                        if response.count != 0 {
                            completion(.failure("This Mobile Number is Already Registered. Please use another Mobile Number to Register"))
                        } else {
                            let response = items as NSArray
                            completion(.success(response))
                        }
                    }
                }
            } else {
                completion(.failure(message))
            }
        }
    }
}
