//
//  LoginModel.swift
//  UDeli
//
//  Created by ARXT Labs on 7/26/18.
//  Copyright © 2018 ARXT Labs. All rights reserved.
//

import Foundation

struct LoginModel {
    // Get Login
    static func signIn(phoneNumber: String, password: String, completion: @escaping (ConnectionResultAsArray) -> ()) {
        Internet.isAvailable { (status, message) in
            if status {
                let predicate = NSPredicate(format: "phonenumber = %@ AND plaintextpass = %@", argumentArray: [phoneNumber, password])
                tCarrier.read(with: predicate) { (result, error) in
                    if let err = error {
                        completion(.failure(err.localizedDescription))
                    } else if let items = result?.items {
                        let response = items as NSArray
                        response.count != 0 ? completion(.success(response)) : completion(.failure("Invalid Mobile Number or Password"))
                    }
                }
            } else {
                completion(.failure(message))
            }
        }
    }
}
