#men BMR =   66 + (6.2 x weight) + (12.7 x height) – (6.76 x age)
#women BMR = 655.1 + (4.35 x weight) + (4.7 x height) – (4.7 x age)

#1.2 points for a person who does little to no exercise
#1.37 points for a slightly active person who does light exercise 1–3 days a week
#1.55 points for a moderately active person who performs moderate exercise 3–5 days a week
#1.725 points for a very active person who exercises hard 6–7 days a week
#1.9 points for an extra active person who either has a physically demanding job or has a particularly challenging exercise routine

#Calories burned per day = points * BMR

#Roughly 1Kg is 7700cal

def install_and_import(package):
    import importlib
    try:
        importlib.import_module(package)
    except ImportError:
        import pip
        pip.main(['install', package])
    finally:
        globals()[package] = importlib.import_module(package)

install_and_import("keyboard")
import math,time
from datetime import datetime

def kj_to_kcal(x):
    return round(x/4.184)

#Drinks
kcal_mountain_dew_600ml = 282
kcal_lipton_peach_iced_tea_500ml = 92
kcal_raspberry_fanta_600ml = 197

kcal_1L_sodastream_creaming_soda = 9.92

#Zambreros
kcal_Zambreros_red_chilli_sauce = 28
kcal_Zambreros_chipotle_sauce = 98

kcal_Zambreros_burrito_without_sauce = 749
kcal_Zambreros_small_burrito_without_sauce = 521
kcal_Zambreros_nachos_without_sauce = 809
kcal_Zambreros_bowl_without_sauce = 465

kcal_Zambreros_burrito = kcal_Zambreros_burrito_without_sauce + kcal_Zambreros_red_chilli_sauce + kcal_Zambreros_chipotle_sauce
kcal_Zambreros_small_burrito = kcal_Zambreros_small_burrito_without_sauce + kcal_Zambreros_red_chilli_sauce + kcal_Zambreros_chipotle_sauce
kcal_Zambreros_nachos = kcal_Zambreros_nachos_without_sauce + kcal_Zambreros_red_chilli_sauce + kcal_Zambreros_chipotle_sauce
kcal_Zambreros_bowl = kcal_Zambreros_bowl_without_sauce + kcal_Zambreros_red_chilli_sauce + kcal_Zambreros_chipotle_sauce

#Subway
kcal_Subway_6_inch_meatball_sub = 585
kcal_Subway_12_inch_meatball_sub = 1170
kcal_Subway_cookie = 0.148

kcal_Subway_6_inch_meatball_sub_and_drink = kcal_Subway_6_inch_meatball_sub + kcal_raspberry_fanta_600ml
kcal_Subway_12_inch_meatball_sub_and_drink = kcal_Subway_12_inch_meatball_sub + kcal_raspberry_fanta_600ml

#Chicken Treat
kcal_Chicken_Treat_chicken_bacon_cheeseburger = kj_to_kcal(1600)
kcal_Chicken_Treat_baconary_burger = 679
kcal_Chicken_Treat_large_chips = 590
kcal_Chicken_Treat_baconary_burger_combo = kcal_Chicken_Treat_baconary_burger + kcal_Chicken_Treat_large_chips + kcal_raspberry_fanta_600ml
kcal_Chicken_Treat_chicken_bacon_cheeseburger_combo = kcal_Chicken_Treat_chicken_bacon_cheeseburger + kcal_Chicken_Treat_large_chips + kcal_raspberry_fanta_600ml

#Dominos
kcal_Dominos_Meatlovers_Pasta = 949
kcal_Dominos_Mac_Cheese_Pasta = 946

#Hungry Jacks
kcal_Hungry_Jacks_bacon_deluxe_hunger_tamers = kj_to_kcal(6628)
kcal_Hungry_Jacks_bacon_deluxe = kj_to_kcal(2350)
kcal_Hungry_Jacks_whopper_with_cheese = kj_to_kcal(3110)
kcal_Hungry_Jacks_grill_masters_cowboy_angus = kj_to_kcal(3980)
kcal_Hungry_Jacks_cheeseburger = kj_to_kcal(1320)
kcal_Hungry_Jacks_carolina_whopper = kj_to_kcal(3840)
kcal_Hungry_Jacks_ultimate_double_whopper = kj_to_kcal(4710)
kcal_Hungry_Jacks_6_nuggets_and_sauce = kj_to_kcal(1131)
kcal_Hungry_Jacks_large_chips_6_nuggets_and_sauce = kj_to_kcal(4061)
kcal_Hungry_Jacks_large_chips_12_nuggets_and_sauce = kj_to_kcal(5192)
kcal_Hungry_Jacks_small_chips = kj_to_kcal(1060)
kcal_Hungry_Jacks_medium_chips = kj_to_kcal(1290)
kcal_Hungry_Jacks_large_chips = kj_to_kcal(1850)
kcal_Hungry_Jacks_small_chips = kj_to_kcal(1060)
kcal_Hungry_Jacks_battered_onion_rings = kj_to_kcal(792)
kcal_Hungry_Jacks_storm_flake = kj_to_kcal(2330)
kcal_Hungry_Jacks_small_hot_chocolate = kj_to_kcal(861)
kcal_Hungry_Jacks_medium_hot_chocolate = kj_to_kcal(1260)
kcal_Hungry_Jacks_large_hot_chocolate = kj_to_kcal(1460)
kcal_Hungry_Jacks_small_drink = kj_to_kcal(600)   #Approximate, changes on drink
kcal_Hungry_Jacks_medium_drink = kj_to_kcal(750)  #Approximate, changes on drink
kcal_Hungry_Jacks_large_drink = kj_to_kcal(1100)  #Approximate, changes on drink

kcal_Hungry_Jacks_bacon_deluxe_large_combo = kcal_Hungry_Jacks_bacon_deluxe + kcal_Hungry_Jacks_large_chips + kcal_Hungry_Jacks_large_drink
kcal_Hungry_Jacks_bacon_deluxe_large_combo_HC = kcal_Hungry_Jacks_bacon_deluxe + kcal_Hungry_Jacks_large_chips + kcal_Hungry_Jacks_large_hot_chocolate
kcal_Hungry_Jacks_bacon_deluxe_medium_combo = kcal_Hungry_Jacks_bacon_deluxe + kcal_Hungry_Jacks_medium_chips + kcal_Hungry_Jacks_medium_drink
kcal_Hungry_Jacks_bacon_deluxe_medium_combo_HC = kcal_Hungry_Jacks_bacon_deluxe + kcal_Hungry_Jacks_medium_chips + kcal_Hungry_Jacks_medium_hot_chocolate
kcal_Hungry_Jacks_bacon_deluxe_small_combo = kcal_Hungry_Jacks_bacon_deluxe + kcal_Hungry_Jacks_small_chips + kcal_Hungry_Jacks_small_drink
kcal_Hungry_Jacks_bacon_deluxe_small_combo_HC = kcal_Hungry_Jacks_bacon_deluxe + kcal_Hungry_Jacks_small_chips + kcal_Hungry_Jacks_small_hot_chocolate

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
kcal_Up_And_Go_Protein_strawberry = 426

#Overrides
BMR_Override = ""
kcal_already_consumed = kcal_Hungry_Jacks_bacon_deluxe_medium_combo_HC
birthdayOverride = "21/08/2000"
genderOverride = "m"

#----------------------------------------------------------------------------------------------------------------------
#----------------------------------------------------------------------------------------------------------------------
#----------------------------------------------------------------------------------------------------------------------

print()
print("------------------------------------------------------------------------")
print("----                         BMR Calculator                         ----")
print("------------------------------------------------------------------------")
print()
print()
print("Description: This program will calculate the amount of calories you burn per day using the Harris-Benedict formula")
print()
print()

if ((BMR_Override=="") or (BMR_Override=="")):
    print()

    if (genderOverride != ""):
        if ((genderOverride.lower() == "m") or (genderOverride.lower() == "male") or (genderOverride.lower() == "man") or (genderOverride.lower() == "boy")):
            male_selected = True
            print("Question 1/5: SKIPPED - Male selected")
        elif ((genderOverride.lower() == "f") or (genderOverride.lower() == "female") or (genderOverride.lower() == "woman") or (genderOverride.lower() == "girl")):
            print("Question 1/5: SKIPPED - Female selected")
        else:
            raise Exception("Invalid gender override option used")
    else:
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

    weight = float(input("Question 2/5: What is your weight (Kg)?  "))
    height = float(input("Question 3/5: What is your height (cm)?  "))
    
    birthday = birthdayOverride
    if (birthdayOverride == ""):
        birthday = input("Question 4/5: What is your birthday(DD/MM/YYYY)?  ")
    else:
        print("Question 4/5: SKIPPED")
    age = (datetime.now() - datetime.strptime(birthday, '%d/%m/%Y')).total_seconds()/60/60/24/365.25
    
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

print()
print()
if (kcal_already_consumed != ""):
    kcalLeft = round(dailyCalBurn - kcal_already_consumed)

    print()
    print("User has already eaten " + str(kcal_already_consumed) + " kcal, which leaves them with " + str(kcalLeft) + " kcal or " + str(round(kcalLeft*4.184)) + " KJ left to eat to maintain equilibrium")

print()
print()
print()
if ((BMR_Override=="") or (BMR_Override=="")):
    print("Calculated a BMR of: " + str(round(resultingBMR,1)) + " with a total daily kcal burn of " + str(round(dailyCalBurn,1)))
else:
    print("Calculated a total daily kcal burn of " + str(round(dailyCalBurn,1)))

print("You could be burning 1Kg in roughly: " + str(round(7700/dailyCalBurn,1)) + " days, or losing " + str(round(7*dailyCalBurn/7700,1)) + " Kg per week without eating anything")
print("After a dangerous period of not eating for a month, that'd give you roughly " + str(round(30*dailyCalBurn/7700,1)) + " Kg of lost weight, although obviously I do not condone this")
print()
print()
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
    spacer3 = " " * (70 - len(mealStr))
    spacer4 = " " * (4 - len(str(leftOverKcal)))
    spacer5 = " " * (6 - len(str(round(leftOverKcal*4.184,1))))
    
    stableWeight = "Unknown"
    print(" - " + str(round(kcal_meal)) + spacer + " kcal or " + str(round(kcal_meal*4.184)) + " KJ" + spacer2 + " (" + str(mealCombo) + ")  " + str(mealComboRounded) + " " + mealStr + " meals with: " + spacer3 + str(leftOverKcal) + spacer4 + " kCal / " + str(round(leftOverKcal*4.184,1)) + spacer5 + " kJ left over")#, which would stabilize your weight at " + str(stableWeight) + " Kg")

print("Zambreros")
printMealPercentages(kcal_Zambreros_burrito + kcal_mountain_dew_600ml,                  "Zambreros burrito and 600mL mountain dew")
printMealPercentages(kcal_Zambreros_burrito + kcal_lipton_peach_iced_tea_500ml,         "Zambreros burrito and 500mL Lipton peach iced tea")
printMealPercentages(kcal_Zambreros_small_burrito + kcal_mountain_dew_600ml,            "Zambreros small burrito and 600mL mountain dew")
printMealPercentages(kcal_Zambreros_small_burrito + kcal_lipton_peach_iced_tea_500ml,   "Zambreros small burrito and 500mL Lipton peach iced tea")
printMealPercentages(kcal_Zambreros_nachos  + kcal_mountain_dew_600ml,                  "Zambreros nachos and 600mL mountain dew")
printMealPercentages(kcal_Zambreros_nachos  + kcal_lipton_peach_iced_tea_500ml,         "Zambreros nachos and 500mL Lipton peach iced tea")

print()
print("Subway")
printMealPercentages(kcal_Subway_6_inch_meatball_sub_and_drink,                         "Subway 6 inch meatball sub and 600mL raspberry fanta")
printMealPercentages(kcal_Subway_6_inch_meatball_sub_and_drink + kcal_Subway_cookie,    "Subway 6 inch meatball sub, 600mL raspberry fanta, and cookie")
printMealPercentages(kcal_Subway_12_inch_meatball_sub_and_drink,                        "Subway 12 inch meatball sub and 600mL raspberry fanta")
printMealPercentages(kcal_Subway_12_inch_meatball_sub_and_drink + kcal_Subway_cookie,   "Subway 12 inch meatball sub, 600mL raspberry fanta, and cookie")

print()
print("Chicken Treat")
printMealPercentages(kcal_Chicken_Treat_baconary_burger_combo,                          "Chicken Treat baconary burger, large chips and drink combo")
printMealPercentages(kcal_Chicken_Treat_chicken_bacon_cheeseburger_combo,               "Chicken Treat chicken bacon cheeseburger, large chips, and drink combo")

print()
print("Dominos")
printMealPercentages(kcal_Dominos_Meatlovers_Pasta,                                     "Dominos Meatlovers Pasta")
printMealPercentages(kcal_Dominos_Mac_Cheese_Pasta,                                     "Dominos Mac and Cheese Pasta")

print()
print("Hungry jacks")
printMealPercentages(kcal_Hungry_Jacks_bacon_deluxe_hunger_tamers,                      "Hungry Jacks Bacon Deluxe Hunger Tamer")
printMealPercentages(kcal_Hungry_Jacks_bacon_deluxe,                                    "Hungry Jacks Bacon Deluxe Burger")

printMealPercentages(kcal_Hungry_Jacks_bacon_deluxe_large_combo,                        "Hungry Jacks Bacon Deluxe Burger Large Combo")
printMealPercentages(kcal_Hungry_Jacks_bacon_deluxe_large_combo_HC,                     "Hungry Jacks Bacon Deluxe Burger Large Combo with Hot Chocolate")
printMealPercentages(kcal_Hungry_Jacks_bacon_deluxe_medium_combo,                       "Hungry Jacks Bacon Deluxe Burger Medium Combo")
printMealPercentages(kcal_Hungry_Jacks_bacon_deluxe_medium_combo_HC,                    "Hungry Jacks Bacon Deluxe Burger Medium Combo with Hot Chocolate")
printMealPercentages(kcal_Hungry_Jacks_bacon_deluxe_small_combo,                        "Hungry Jacks Bacon Deluxe Burger Small Combo")
printMealPercentages(kcal_Hungry_Jacks_bacon_deluxe_small_combo_HC,                     "Hungry Jacks Bacon Deluxe Burger Small Combo with Hot Chocolate")


printMealPercentages(kcal_Hungry_Jacks_whopper_with_cheese,                             "Hungry Jacks Whopper with Cheese")
printMealPercentages(kcal_Hungry_Jacks_grill_masters_cowboy_angus,                      "Hungry Jacks Grill Masters Cowboy Angus")
printMealPercentages(kcal_Hungry_Jacks_cheeseburger,                                    "Hungry Jacks Cheeseburger")
printMealPercentages(kcal_Hungry_Jacks_carolina_whopper,                                "Hungry Jacks Carolina Whopper")
printMealPercentages(kcal_Hungry_Jacks_ultimate_double_whopper,                         "Hungry Jacks Ultimate Double Whopper")
printMealPercentages(kcal_Hungry_Jacks_6_nuggets_and_sauce,                             "Hungry Jacks 6 Nuggets and Sauce")
printMealPercentages(kcal_Hungry_Jacks_large_chips_6_nuggets_and_sauce,                 "Hungry Jacks Large Chips, 6 Nuggets, and Sauce")
printMealPercentages(kcal_Hungry_Jacks_large_chips_12_nuggets_and_sauce,                "Hungry Jacks Large Chips, 12 Nuggets, and Sauce")
printMealPercentages(kcal_Hungry_Jacks_large_chips,                                     "Hungry Jacks Large Chips")
printMealPercentages(kcal_Hungry_Jacks_small_chips,                                     "Hungry Jacks Small Chips")
printMealPercentages(kcal_Hungry_Jacks_battered_onion_rings,                            "Hungry Jacks Battered Onion Rings")
printMealPercentages(kcal_Hungry_Jacks_storm_flake,                                     "Hungry Jacks Storm Flake")

print()
print("Misc")
printMealPercentages(kcal_Suimin_braised_beef,                                          "Suimin braised beef noodle cup")
printMealPercentages(kcal_peanut_butter_sandwich,                                       "Peanut Butter Sandwich")

time.sleep(2)
print()
print()
print()
print("------------------------------------------")
print()
input("Press Enter to Close")
