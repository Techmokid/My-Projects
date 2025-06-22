import json

with open("vanilla-2.0.10.json") as f:
    data = json.load(f)

recipes = data["recipes"]

smelting = []
assembling = []
oilProcessing = []
chemistry = []
centrifuging = []
other = []

yellow_belt_speed = 900
red_belt_speed = 1800
blue_belt_speed = 2700

assembler1_speed = 0.5
assembler2_speed = 0.75
assembler3_speed = 1.25

for r in recipes:
    category = r.get("category", "")

    # Add in time to craft values
    seconds_per_craft = float(r["energy_required"]) # I have checked and confirmed, all incoming data has "energy_required" for some reason, so no null check required here
    crafts_per_minute = 60 / seconds_per_craft
    r["Items per Minute - Assembling Machine 1"] = assembler1_speed*crafts_per_minute
    r["Items per Minute - Assembling Machine 2"] = assembler2_speed*crafts_per_minute
    r["Items per Minute - Assembling Machine 3"] = assembler3_speed*crafts_per_minute
    
    if category == "smelting":
        smelting.append(r)
    elif category in ["crafting", "advanced-crafting", "crafting-with-fluid"]:
        r["Assembling Machine 1 required to fill yellow belt"] =    yellow_belt_speed   / (assembler1_speed*crafts_per_minute)
        r["Assembling Machine 1 required to fill red belt"] =       red_belt_speed      / (assembler1_speed*crafts_per_minute)
        r["Assembling Machine 1 required to fill blue belt"] =      blue_belt_speed     / (assembler1_speed*crafts_per_minute)
        r["Assembling Machine 2 required to fill yellow belt"] =    yellow_belt_speed   / (assembler2_speed*crafts_per_minute)
        r["Assembling Machine 2 required to fill red belt"] =       red_belt_speed      / (assembler2_speed*crafts_per_minute)
        r["Assembling Machine 2 required to fill blue belt"] =      blue_belt_speed     / (assembler2_speed*crafts_per_minute)
        r["Assembling Machine 3 required to fill yellow belt"] =    yellow_belt_speed   / (assembler3_speed*crafts_per_minute)
        r["Assembling Machine 3 required to fill red belt"] =       red_belt_speed      / (assembler3_speed*crafts_per_minute)
        r["Assembling Machine 3 required to fill blue belt"] =      blue_belt_speed     / (assembler3_speed*crafts_per_minute)
        assembling.append(r)
    elif category == "oil-processing":
        oilProcessing.append(r)
    elif category == "chemistry":
        chemistry.append(r)
    elif category == "centrifuging":
        centrifuging.append(r)
    else:
        other.append(r)

# Save to separate files
with open("smelting_recipes.json", "w") as f:
    json.dump(smelting, f, indent=2)
with open("assembling_recipes.json", "w") as f:
    json.dump(assembling, f, indent=2)
with open("oilProcessing.json", "w") as f:
    json.dump(oilProcessing, f, indent=2)
with open("chemistry.json", "w") as f:
    json.dump(chemistry, f, indent=2)
with open("centrifuging.json", "w") as f:
    json.dump(centrifuging, f, indent=2)
with open("other.json", "w") as f:
    json.dump(other, f, indent=2)
    
print(f"Smelting: {len(smelting)} recipes")
print(f"Assembling: {len(assembling)} recipes")
print(f"Oil Processing: {len(oilProcessing)} recipes")
print(f"Chemistry: {len(chemistry)} recipes")
print(f"Centrifuging: {len(centrifuging)} recipes")
print(f"Other: {len(other)} recipes")

