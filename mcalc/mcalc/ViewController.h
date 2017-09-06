//
//  ViewController.h
//  mcalc
//
//  Created by Kishore Atreya on 4/14/14.
//  Copyright (c) 2014 ___FULLUSERNAME___. All rights reserved.
//

#import <UIKit/UIKit.h>

@interface ViewController : UIViewController
{
}

/*
 * Properties
 */

@property (nonatomic) float rate;
@property (nonatomic) int   term;
@property (nonatomic) float loan;
@property (nonatomic) BOOL  taxPmi;

// UITextField Property, used to access loan amount in dollars
@property (weak, nonatomic) IBOutlet UITextField        * loanAmtTextField;

// UISlider Property, used to update hte rateVal display
@property (weak, nonatomic) IBOutlet UISlider           * rateSlider;

// UILabel Property, used to access the rate val from the slider
@property (weak, nonatomic) IBOutlet UILabel            * rateLabel;

// UISegmentedControl Property, used to select number of years for loan term
@property (weak, nonatomic) IBOutlet UISegmentedControl * termYrsSc;

// UISwitch Property, used to determine whether or not to include PMI in calculation
@property (weak, nonatomic) IBOutlet UISwitch           * taxPmiSwitch;

// UILabel Property, used to update the Total Monthly payment
@property (weak, nonatomic) IBOutlet UILabel            * monthlyPaymentLabel;

// UIButton Property, used to trigger the Monthly payment calculation
@property (weak, nonatomic) IBOutlet UIButton           * calculateButton;

/*
 * Instance Methods
 */

// IBAction Event Handlers
- (IBAction) sliderChanged:(UISlider *)sender;
- (IBAction) segmentedControlChanged:(UISegmentedControl *)sender;
- (IBAction) loanEntered:(UITextField *)sender;
- (IBAction) dismissKeyboard;
- (IBAction) calculateButtonPushed;
- (IBAction) taxPmiSwitchTriggered:(UISwitch *)sender;
@end
