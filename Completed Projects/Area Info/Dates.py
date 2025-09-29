from datetime import date, datetime, timedelta

def easter_sunday(year: int) -> date:
    # Anonymous Gregorian algorithm
    a = year % 19
    b = year // 100
    c = year % 100
    d = b // 4
    e = b % 4
    f = (b + 8) // 25
    g = (b - f + 1) // 3
    h = (19 * a + b - d - g + 15) % 30
    i = c // 4
    k = c % 4
    l = (32 + 2 * e + 2 * i - h - k) % 7
    m = (a + 11 * h + 22 * l) // 451
    month = (h + l - 7 * m + 114) // 31
    day = ((h + l - 7 * m + 114) % 31) + 1
    return date(year, month, day)

def easter_monday(year: int) -> date:
    return easter_sunday(year) + timedelta(days=1)

def first_monday(year: int, month: int) -> date:
    d = date(year, month, 1)
    return d + timedelta(days=(7 - d.weekday()) % 7)  # Monday=0

def last_monday(year: int, month: int) -> date:
    # Start at last day of the month, step back to Monday
    if month == 12:
        end = date(year, 12, 31)
    else:
        end = date(year, month + 1, 1) - timedelta(days=1)
    return end - timedelta(days=(end.weekday() - 0) % 7)

def wa_public_holidays(year: int):
    # Sources: WA rules (first/last Monday patterns); note: some years have proclamations that shift dates —
    # this covers the standard pattern.
    easter = easter_sunday(year)
    holidays = [
        ["New Year’s Day", date(year, 1, 1)],
        ["Australia Day", date(year, 1, 26)],
        ["Labour Day (WA)", first_monday(year, 3)],
        ["Good Friday", easter - timedelta(days=2)],
        ["Easter Sunday", easter],
        ["Easter Monday", easter + timedelta(days=1)],
        ["ANZAC Day", date(year, 4, 25)],
        ["WA Day", first_monday(year, 6)],
        # King’s Birthday in WA is typically last Monday of September (but can vary by proclamation).
        ["King’s Birthday (WA)", last_monday(year, 9)],
        ["Christmas Day", date(year, 12, 25)],
        ["Boxing Day", date(year, 12, 26)],
    ]
    holidays.sort(key=lambda x: x[1])
    return holidays

def upcoming_wa_public_holidays():
    today = date.today()
    this_year = wa_public_holidays(today.year)
    next_year = wa_public_holidays(today.year + 1)

    # Here we want to select which of the two holidays depending on if this years version has already passed or not
    upcoming = []
    for (name, d), (_, d_next) in zip(this_year, next_year):
        # if this year's date has passed, take next year's version
        chosen = d if d >= today else d_next
        upcoming.append([name, chosen])
    
    upcoming.sort(key=lambda x: x[1])
    return upcoming

if __name__ == "__main__":
    for date in upcoming_wa_public_holidays():
        print(date)
    for i in range(5):
        print()
    input("--- Press Enter to close ---")
