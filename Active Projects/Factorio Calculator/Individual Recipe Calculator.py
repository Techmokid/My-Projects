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

def calculate_assemblers_needed(recipe_key, assembler_tier, target_output_per_min):
    if assembler_tier not in assembler_speeds:
        raise ValueError("Assembler tier must be 1, 2, or 3")
    
    if target_output_per_min is None:
        raise ValueError("Must specify either belt_type or target_output_per_min")

    recipe = recipe_dict.get(recipe_key)
    if not recipe:
        raise ValueError(f"Recipe '{recipe_key}' not found.")

    result_amount = recipe["results"][0]["amount"]
    craft_time = float(recipe["energy_required"])
    speed = assembler_speeds[assembler_tier]

    crafts_per_min_per_assembler = (60 / craft_time) * speed
    items_per_min_per_assembler = crafts_per_min_per_assembler * result_amount

    assembler_count = target_output_per_min / items_per_min_per_assembler
    assembler_count_rounded = math.ceil(assembler_count)
    actual_output = assembler_count_rounded * items_per_min_per_assembler

    # Build data dict instead of printing
    result = {
        "recipe_key": recipe_key,
        "localized_name": recipe["localized_name"]["en"],
        "assembler_tier": assembler_tier,
        "assemblers_needed": assembler_count,
        "assemblers_needed_rounded": assembler_count_rounded,
        "produces_per_min": actual_output,
        "ingredients": []
    }

    for ing in recipe["ingredients"]:
        ing_name = ing["name"]
        ing_amount = ing["amount"]
        total_ing_per_min = ing_amount * crafts_per_min_per_assembler * assembler_count_rounded

        ing_data = {
            "name": ing_name,
            "amount_per_min": total_ing_per_min
        }

        # Recursively add sub-recipe data if available
        if ing_name in recipe_dict:
            ing_data["recipe"] = calculate_assemblers_needed(
                ing_name, assembler_tier, target_output_per_min=total_ing_per_min
            )

        result["ingredients"].append(ing_data)

    return result

# === Example usage ===
if __name__ == "__main__":
    output_data = calculate_assemblers_needed("artillery-wagon", 1, 1)

    # Save to JSON file
    with open("artillery_wagon_assemblers.json", "w") as f:
        json.dump(output_data, f, indent=4)

    print("Calculation saved to artillery_wagon_assemblers.json")
