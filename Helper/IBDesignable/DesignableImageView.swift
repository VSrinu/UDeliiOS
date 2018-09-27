//
//  UDProfileViewController.swift
//  UDeli
//
//  Created by ARXT Labs on 6/28/18.
//  Copyright © 2018 ARXT Labs. All rights reserved.
//

import UIKit

@IBDesignable class DesignableImageView: UIImageView {
    @IBInspectable var cornerRadius: CGFloat = 0 {
        didSet {
            self.layer.cornerRadius = cornerRadius
            self.layer.masksToBounds = true
        }
    }
    
    @IBInspectable var borderWidth: CGFloat = 0 {
        didSet {
            self.layer.borderWidth = borderWidth
        }
    }
    
    @IBInspectable override var borderColor: UIColor? {
        didSet {
            self.layer.borderColor = borderColor?.cgColor
        }
    }
}
