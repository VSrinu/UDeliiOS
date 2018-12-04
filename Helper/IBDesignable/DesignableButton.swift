//
//  UDProfileViewController.swift
//  oogioogi
//
//  Created by ARXT Labs on 6/28/18.
//  Copyright © 2018 ARXT Labs. All rights reserved.
//

import UIKit

@IBDesignable class DesignableButton: UIButton {
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
    
    @IBInspectable var bottomBorderColor: UIColor? {
        didSet {
            
        }
    }
    
    @IBInspectable var bottomBorderHeight: CGFloat = 0 {
        didSet {
            let bottomBorder = CALayer()
            bottomBorder.frame = CGRect(x:0, y:self.frame.size.height - bottomBorderHeight, width:self.frame.size.width, height:bottomBorderHeight)
            bottomBorder.backgroundColor = bottomBorderColor?.cgColor
            self.layer.addSublayer(bottomBorder)
        }
    }
    
    @IBInspectable var leftTopRadius : CGFloat = 0 {
        didSet{
            self.applyMask()
        }
    }
    @IBInspectable var rightTopRadius : CGFloat = 0 {
        didSet{
            self.applyMask()
        }
    }
    @IBInspectable var rightBottomRadius : CGFloat = 0 {
        didSet{
            self.applyMask()
        }
    }
    
    @IBInspectable var leftBottomRadius : CGFloat = 0 {
        didSet{
            self.applyMask()
        }
    }
    
    func applyMask() {
        let shapeLayer = CAShapeLayer(layer: self.layer)
        shapeLayer.path = self.pathForCornersRounded(rect:self.bounds).cgPath
        shapeLayer.frame = self.bounds
        shapeLayer.masksToBounds = true
        self.layer.mask = shapeLayer
    }
    
    func pathForCornersRounded(rect:CGRect) ->UIBezierPath {
        let path = UIBezierPath()
        path.move(to: CGPoint(x: 0 + leftTopRadius , y: 0))
        path.addLine(to: CGPoint(x: rect.size.width - rightTopRadius , y: 0))
        path.addQuadCurve(to: CGPoint(x: rect.size.width , y: rightTopRadius), controlPoint: CGPoint(x: rect.size.width, y: 0))
        path.addLine(to: CGPoint(x: rect.size.width , y: rect.size.height - rightBottomRadius))
        path.addQuadCurve(to: CGPoint(x: rect.size.width - rightBottomRadius , y: rect.size.height), controlPoint: CGPoint(x: rect.size.width, y: rect.size.height))
        path.addLine(to: CGPoint(x: leftBottomRadius , y: rect.size.height))
        path.addQuadCurve(to: CGPoint(x: 0 , y: rect.size.height - leftBottomRadius), controlPoint: CGPoint(x: 0, y: rect.size.height))
        path.addLine(to: CGPoint(x: 0 , y: leftTopRadius))
        path.addQuadCurve(to: CGPoint(x: 0 + leftTopRadius , y: 0), controlPoint: CGPoint(x: 0, y: 0))
        path.close()
        return path
    }
}
