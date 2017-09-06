//
//  ViewController.m
//  mcalc
//
//  Created by Kishore Atreya on 4/14/14.
//  Copyright (c) 2014 ___FULLUSERNAME___. All rights reserved.
//

#import "ViewController.h"
#import <math.h>

#define ANNUAL_RATE_DIVIDER 1200
#define PMI_MULTIPLIER      0.001
#define MONTHS_IN_YEAR      12

@interface ViewController ()

@end

@implementation ViewController

/*
 * Synthesized properties
 */
@synthesize loanAmtTextField, rateSlider, rateLabel;
@synthesize termYrsSc, taxPmiSwitch, monthlyPaymentLabel, calculateButton;
@synthesize rate, term, loan, taxPmi;

- (void) viewDidLoad
{
    [super viewDidLoad];
	// Do any additional setup after loading the view, typically from a nib.
    
    // Initialize the default rate from the default slider value and update the rate label
    [self setRate:[rateSlider value]];
    [rateLabel setText:[NSString stringWithFormat:@"%.1f%%", [self rate]]];
    NSLog(@"Default interest rate %.1f", [self rate]);
    
    // Initialize default term value from the default selected segmented control value
    [self setTerm:[[termYrsSc titleForSegmentAtIndex:[termYrsSc selectedSegmentIndex]] intValue]];
    for(int i = 0; i < 3; i++)
    {
        NSLog(@"term value at idx %d: %@", i, [termYrsSc titleForSegmentAtIndex:i]);
    }
    
    // Default value of $0.00 to be shown as the monthly payment display to user
    [monthlyPaymentLabel setText:[NSString stringWithFormat:@"$%.2f", 0.0]];
    
    NSLog(@"Default term value in years %d", [self term]);
    
    NSLog(@"Default loan value in dollars %d", 0);
}

- (void) didReceiveMemoryWarning
{
    [super didReceiveMemoryWarning];
    // Dispose of any resources that can be recreated.
}

/// This method is a "private" method to this object, it is not exposed to
/// the outside world
- (float) calculateMonthlyPayment
{
    float payment   = 0.0;    // Initialize payment value to 0.0 to start;
    float totMonths = ([self term] * MONTHS_IN_YEAR); // Total months in term
    
    if([self rate] == 0.0)
    {
        // If the interest rate is 0.0%
        payment = [self loan] / totMonths;
        NSLog(@"The interest rate is 0.0%%, monthly payment without PMI is %.2f", payment);
    }
    else
    {
        float monthInt = [self rate] / ANNUAL_RATE_DIVIDER;
        payment  = [self loan] * ((monthInt) / (1 - powf((1 + monthInt), (0 - totMonths))));
        NSLog(@"The interest rate is %.1f, monthly payment without PMI is %.2f", [self rate],  payment);
    }
 
    if([self taxPmi] == YES)
    {
        float pmiVal = [self loan] * PMI_MULTIPLIER;
        NSLog(@"PMI is set, adding 0.1%% of loan amount (%.2f) to monthly payment", pmiVal);
        
        payment += pmiVal;
    }
    
    NSLog(@"The final monthly payment value is %.2f dollars", payment);
    
    return payment;
}

- (IBAction) sliderChanged:(UISlider *)sender
{
    // Retrieve the new value from the slider and set it
    [self setRate:[sender value]];
    
    // Update the rateLabel
    [rateLabel setText:[NSString stringWithFormat:@"%.1f%%", [self rate]]];
    
    NSLog(@"New interest rate %.1f", [self rate]);
}

- (IBAction) segmentedControlChanged:(UISegmentedControl *)sender
{
    // Retrieve the new value from the segmented control and set it
    [self setTerm:[[sender titleForSegmentAtIndex:[termYrsSc selectedSegmentIndex]] intValue]];
    NSLog(@"New term value in years %d", [self term]);
}

- (IBAction) loanEntered:(UITextField *) sender
{
    // User entered a new loan amount in text field so retreive it and store it
    [self setLoan: [[sender text] floatValue]];
    NSLog(@"New loan value in dollars %f", [self loan]);
}

- (IBAction) dismissKeyboard
{
    if([[self loanAmtTextField] isFirstResponder])
    {
        [[self loanAmtTextField] resignFirstResponder];
        NSLog(@"Keyboard dismissed from tap away");
        
        // Read directly from IBOutlet UITextField stored in class to update the
        // loan amount
        [self setLoan:[[loanAmtTextField text] floatValue]];
        NSLog(@"New loan value in dollars %f", [self loan]);
    }
}

- (IBAction) calculateButtonPushed
{
    float payment;

    NSLog(@"Monthly Payment calculation triggered");
    
    // Calculate the new monthly payment
    payment = [self calculateMonthlyPayment];

    // Update the monthly payment label with the result
    [monthlyPaymentLabel setText:[NSString stringWithFormat:@"$%.2f", payment]];
}

- (IBAction) taxPmiSwitchTriggered:(UISwitch *)sender
{
    [self setTaxPmi:[sender isOn]];
    NSLog(@"Tax PMI Switch triggered, switch is now %@", ([sender isOn]) ? @"ON" : @"OFF");
}

@end
