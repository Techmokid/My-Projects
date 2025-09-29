import requests
import xml.etree.ElementTree as ET
import re
from typing import Optional, Tuple

RSS_URL = "https://api.emergency.wa.gov.au/v1/rss/total-fire-bans"
TEXT_URL = "https://www.emergency.wa.gov.au/text-version"

HEADERS = {
    "User-Agent": "Mozilla/5.0 (Windows NT 10.0; Win64; x64)",
    "Accept": "application/xml, text/xml, text/html;q=0.9,*/*;q=0.8",
    "Accept-Language": "en-AU,en;q=0.9",
    "Connection": "close",
}

def _contains_lga(text: str, lga: str) -> bool:
    return re.search(rf"\b{re.escape(lga)}\b", text, flags=re.IGNORECASE) is not None

def _check_rss_for_lga(lga: str, timeout: float) -> Optional[bool]:
    r = requests.get(RSS_URL, headers=HEADERS, timeout=timeout)
    r.raise_for_status()
    ctype = r.headers.get("Content-Type", "")
    if "xml" not in ctype and "rss" not in ctype:
        return None  # not RSS/XML, bail to fallback
    root = ET.fromstring(r.content)
    # RSS 2.0: <rss><channel><item><title>…</title><description>…</description></item>…
    for item in root.findall(".//item"):
        text = " ".join([
            (item.findtext("title") or ""),
            (item.findtext("description") or ""),
        ])
        if _contains_lga(text, lga):
            return True
    # If feed has items but none match your LGA, treat as False
    return False

def _check_text_page_for_lga(lga: str, timeout: float) -> Optional[bool]:
    r = requests.get(TEXT_URL, headers=HEADERS, timeout=timeout)
    r.raise_for_status()
    html = r.text
    # Grab the "Total Fire Bans" section (Today/Now).
    # The text-version page is server-rendered and includes lists of LGAs.
    m = re.search(r"Total\s*Fire\s*Bans.*?(?:<ul[^>]*>.*?</ul>|<ol[^>]*>.*?</ol>)",
                  html, flags=re.IGNORECASE | re.DOTALL)
    if not m:
        return None
    tfb_block = re.sub(r"<[^>]+>", " ", m.group(0))  # strip tags for easy matching
    return True if _contains_lga(tfb_block, lga) else False

def firebanInfo(lga_name: str = "Mundaring", timeout: float = 8.0) -> Tuple[Optional[bool], str]:
    """
    Returns (is_ban, info_text):
      True  -> TFB active for the LGA
      False -> No TFB for the LGA (based on feeds checked)
      None  -> Couldn’t determine (network/format change)
    """
    # 1) Preferred: RSS feed
    try:
        rss_result = _check_rss_for_lga(lga_name, timeout)
        if rss_result is True:
            return True, f"Total Fire Ban ACTIVE for {lga_name} (RSS)."
        if rss_result is False:
            return False, f"No Total Fire Ban for {lga_name} (RSS)."
    except Exception as e:
        pass  # fall back

    # 2) Fallback: text-only page
    try:
        txt_result = _check_text_page_for_lga(lga_name, timeout)
        if txt_result is True:
            return True, f"Total Fire Ban ACTIVE for {lga_name} (text page)."
        if txt_result is False:
            return False, f"No Total Fire Ban for {lga_name} (text page)."
    except Exception:
        pass

    return None, "Couldn’t confirm from Emergency WA (network/format issue)."

if __name__ == "__main__":
    print("This is the wrong file to open. Try running \"Today Info.py\" instead")
    for i in range(5):
        print()
    input("--- Press Enter to close ---")
