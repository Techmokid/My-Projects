#men BMR =   66 + (6.2 x weight) + (12.7 x height) – (6.76 x age)
#women BMR = 655.1 + (4.35 x weight) + (4.7 x height) – (4.7 x age)

#1.2 points for a person who does little to no exercise
#1.37 points for a slightly active person who does light exercise 1–3 days a week
#1.55 points for a moderately active person who performs moderate exercise 3–5 days a week
#1.725 points for a very active person who exercises hard 6–7 days a week
#1.9 points for an extra active person who either has a physically demanding job or has a particularly challenging exercise routine

#Calories burned per day = points * BMR

#Roughly 1Kg is 7700cal

import keyboard,math

#Drinks
kcal_mountain_dew_500ml = 240
kcal_lipton_peach_iced_tea_500ml = 92
kcal_raspberry_fanta_600ml = 197

kcal_1L_sodastream_creaming_soda = 9.92

#Zambreros
kcal_Zambreros_red_chilli_sauce = 28
kcal_Zambreros_burrito_without_sauce = 749
kcal_Zambreros_small_burrito_without_sauce = 521
kcal_Zambreros_nachos_without_sauce = 809

kcal_Zambreros_burrito = kcal_Zambreros_burrito_without_sauce + kcal_Zambreros_red_chilli_sauce
kcal_Zambreros_small_burrito = kcal_Zambreros_small_burrito_without_sauce + kcal_Zambreros_red_chilli_sauce
kcal_Zambreros_nachos = kcal_Zambreros_nachos_without_sauce + kcal_Zambreros_red_chilli_sauce

#Subway
kcal_Subway_6_inch_meatball_sub = 585
kcal_Subway_12_inch_meatball_sub = 1170
kcal_Subway_cookie = 0.148

kcal_Subway_6_inch_meatball_sub_and_drink = kcal_Subway_6_inch_meatball_sub + kcal_raspberry_fanta_600ml
kcal_Subway_12_inch_meatball_sub_and_drink = kcal_Subway_12_inch_meatball_sub + kcal_raspberry_fanta_600ml

#Dominos
kcal_Dominos_Meatlovers_Pasta = 949
kcal_Dominos_Mac_Cheese_Pasta = 946

#Krispy Kremes
kcal_Krispy_Kreme_original_glazed = 131
kcal_Krispy_Kreme_vanilla_slice = 230
kcal_Krispy_Kreme_choc_custard_filled = 213
kcal_Krispy_Kreme_cookies_and_kreme = 306

#Suimin
kcal_Suimin_braised_beef = 344

#Misc
kcal_white_bread_slice = 66
kcal_peanut_butter_sandwich = 2*kcal_white_bread_slice + 6.285851*73.60875 #1g peanut butter = 6.285851kcal

#Overrides
BMR_Override = 1898
kcal_already_consumed = kcal_lipton_peach_iced_tea_500ml + kcal_Zambreros_burrito

#----------------------------------------------------------------------------------------------------------------------
#----------------------------------------------------------------------------------------------------------------------
#----------------------------------------------------------------------------------------------------------------------

print()
print("--------------")
print("BMR Calculator")
print("--------------")
print()
print("This program will calculate the amount of calories you burn per day using the Harris-Benedict formula")
print()

if ((BMR_Override=="") or (BMR_Override=="")):
    print()
    print("Question 1/5: Are you (M)ale or (F)emale in biology?")

    male_selected = False
    while True:  # making a loop
        try:  # used try so that if user pressed other than the given key error will not be shown
            m_key = keyboard.is_pressed('m')
            f_key = keyboard.is_pressed('f')
            if m_key:  # if key 'q' is pressed 
                print('You selected male')
                male_selected = True
                break  # finishing the loop
            if f_key:  # if key 'q' is pressed 
                print('You selected female')
                break  # finishing the loop
        except:
            break  # if user pressed a key other than the given key the loop will break

    print()
    weight = float(input("Question 2/5: What is your weight (Kg)?  "))
    height = float(input("Question 3/5: What is your height (cm)?  "))
    age    = float(input("Question 4/5: What is your age (years)?  "))

    resultingBMR = 0
    if (male_selected):
        resultingBMR = 88.362 + (13.397 * weight) + (4.799 * height) - (5.677 * age)
    else:
        resultingBMR = 447.593 + (9.247 * weight) + (3.098 * height) - (4.33 * age)
else:
    print()
    print("!!!BMR value override used!!!")
    resultingBMR = BMR_Override

resultingActivity = 0
while(resultingActivity == 0):
    if ((BMR_Override=="") or (BMR_Override=="")):
        activity = input("Question 5/5: From a scale of 1 to 5 (1 being little to no activity, 5 being extremely physically active) \n - How physically active are you in your daily life?  ")
    else:
        activity = input("From a scale of 1 to 5 (1 being little to no activity, 5 being extremely physically active) \n - How physically active are you in your daily life?  ")
    
    if (activity == "1"):
        resultingActivity = 1.2
    elif(activity == "2"):
        resultingActivity = 1.37
    elif(activity == "3"):
        resultingActivity = 1.55
    elif(activity == "4"):
        resultingActivity = 1.725
    elif(activity == "5"):
        resultingActivity = 1.9
    else:
        print("Error: " + activity + " is not an integer between 1 and 5")
dailyCalBurn = resultingActivity * resultingBMR

if (kcal_already_consumed != ""):
    kcalLeft = round(dailyCalBurn - kcal_already_consumed)

    print()
    print("User has already eaten " + str(kcal_already_consumed) + " kcal, which leaves them with " + str(kcalLeft) + " kcal or " + str(round(kcalLeft*4.184)) + " KJ left to eat to maintain equilibrium")

print()
if ((BMR_Override=="") or (BMR_Override=="")):
    print("Calculated a BMR of: " + str(round(resultingBMR,1)) + " with a total daily kcal burn of " + str(round(dailyCalBurn,1)))
else:
    print("Calculated a total daily kcal burn of " + str(round(dailyCalBurn,1)))

print("You could be burning 1Kg in roughly: " + str(round(7700/dailyCalBurn,1)) + " days, or losing " + str(round(7*dailyCalBurn/7700,1)) + " Kg per week without eating anything")
print("After a dangerous period of not eating for a month, that'd give you roughly " + str(round(30*dailyCalBurn/7700,1)) + " Kg of lost weight, although obviously I do not condone this")
print()

if ((BMR_Override=="") or (BMR_Override=="")):
    print("That works out as:")
else:
    print("After consuming " + str(kcal_already_consumed) + " kcal, that works out as:")
if (kcal_already_consumed != ""):
    dailyCalBurn -= kcal_already_consumed

def printMealPercentages(kcal_meal, mealStr):
    global dailyCalBurn,height,age
    
    mealCombo = round(dailyCalBurn/kcal_meal,1)
    mealComboRounded = math.floor(dailyCalBurn/kcal_meal)
    leftOverKcal = round(dailyCalBurn - mealComboRounded * kcal_meal)
    spacer = " " * (4 - len(str(round(kcal_meal))))
    spacer2 = " " * (4 - len(str(round(kcal_meal*4.184))))

    stableWeight = "Unknown"
    print(" - " + str(round(kcal_meal)) + spacer + " kcal or " + str(round(kcal_meal*4.184)) + " KJ" + spacer2 + " (" + str(mealCombo) + ")  " + str(mealComboRounded) + " " + mealStr + " meals with " + str(leftOverKcal) + " kcal left over")#, which would stabilize your weight at " + str(stableWeight) + " Kg")

printMealPercentages(kcal_Zambreros_burrito + kcal_mountain_dew_500ml,                "Zambreros burrito and 500mL mountain dew")
printMealPercentages(kcal_Zambreros_burrito + kcal_lipton_peach_iced_tea_500ml,       "Zambreros burrito and 500mL Lipton peach iced tea")
printMealPercentages(kcal_Zambreros_small_burrito + kcal_mountain_dew_500ml,          "Zambreros small burrito and 500mL mountain dew")
printMealPercentages(kcal_Zambreros_small_burrito + kcal_lipton_peach_iced_tea_500ml, "Zambreros small burrito and 500mL Lipton peach iced tea")
printMealPercentages(kcal_Zambreros_nachos  + kcal_mountain_dew_500ml,                "Zambreros nachos and 500mL mountain dew")
printMealPercentages(kcal_Zambreros_nachos  + kcal_lipton_peach_iced_tea_500ml,       "Zambreros nachos and 500mL Lipton peach iced tea")

printMealPercentages(kcal_Subway_6_inch_meatball_sub_and_drink,                       "Subway 6 inch meatball sub and 600mL raspberry fanta")
printMealPercentages(kcal_Subway_6_inch_meatball_sub_and_drink + kcal_Subway_cookie,  "Subway 6 inch meatball sub, 600mL raspberry fanta, and cookie")
printMealPercentages(kcal_Subway_12_inch_meatball_sub_and_drink,                      "Subway 12 inch meatball sub and 600mL raspberry fanta")
printMealPercentages(kcal_Subway_12_inch_meatball_sub_and_drink + kcal_Subway_cookie, "Subway 12 inch meatball sub, 600mL raspberry fanta, and cookie")

printMealPercentages(kcal_Suimin_braised_beef,                                        "Suimin braised beef noodle cup")
printMealPercentages(kcal_peanut_butter_sandwich,                                     "Peanut Butter Sandwich")
