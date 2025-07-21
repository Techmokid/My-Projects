import json
import math

# Load recipe data
with open("assembling_recipes.json") as f:
    recipes = json.load(f)

# Fast lookup
recipe_dict = {r["key"]: r for r in recipes}

# Constants
assembler_speeds = {1: 0.5, 2: 0.75, 3: 1.25}
belt_speeds = {"yellow": 900, "red": 1800, "blue": 2700}

def calculate_assemblers_needed(recipe_key, assembler_tier, target_output_per_min, depth=0):
    indent = "        " * depth

    if assembler_tier not in assembler_speeds:
        raise ValueError("Assembler tier must be 1, 2, or 3")
    
    if target_output_per_min is None:
        raise ValueError("Must specify either belt_type or target_output_per_min")

    recipe = recipe_dict.get(recipe_key)
    if not recipe:
        print(f"{indent}❌ Recipe '{recipe_key}' not found.")
        return

    result_amount = recipe["results"][0]["amount"]
    craft_time = float(recipe["energy_required"])
    speed = assembler_speeds[assembler_tier]

    crafts_per_min_per_assembler = (60 / craft_time) * speed
    items_per_min_per_assembler = crafts_per_min_per_assembler * result_amount

    assembler_count = target_output_per_min / items_per_min_per_assembler
    assembler_count_rounded = math.ceil(assembler_count)
    actual_output = assembler_count_rounded * items_per_min_per_assembler

    belt_info = f" to output at {target_output_per_min:.2f}/min"
    print(f"{indent}🔧 {recipe['localized_name']['en']} using {assembler_count:.2f} x Assembler {assembler_tier}:")

    #if assembler_count != assembler_count_rounded:
    #    print(f"{indent}  ➤ {assembler_count:.2f} assemblers needed (rounded up to {assembler_count_rounded})")
    #else:
    #    print(f"{indent}  ➤ {assembler_count} assemblers needed")
    print(f"{indent}  ➤ Produces {actual_output:.2f} items/min")

    print(f"{indent}  🧾 Requires (per minute):")
    for ing in recipe["ingredients"]:
        ing_name = ing["name"]
        ing_amount = ing["amount"]
        total_ing_per_min = ing_amount * crafts_per_min_per_assembler * assembler_count_rounded
        print(f"{indent}    - {total_ing_per_min:.2f} x {ing_name}/min")

        if ing_name in recipe_dict:
            calculate_assemblers_needed(ing_name, assembler_tier, target_output_per_min=total_ing_per_min, depth=depth + 1)

# === Example usage ===
if __name__ == "__main__":
    calculate_assemblers_needed("chemical-science-pack", 2, belt_speeds["yellow"]/2)
