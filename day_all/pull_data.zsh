#!/bin/zsh

# Read the session cookie from the file
SESSION_COOKIE=$(cat ../cookie.txt)

# Read the year from the year.txt file
YEAR=$(cat ../year.txt)

# Loop through days 1 to 25
for DAY_NUMBER in {1..25}; do
  # Format the day with leading zeros if needed (e.g., 01, 02)

  # Set the output file name
  OUTPUT_FILE="puzzle_day_${DAY_NUMBER}.txt"

  # Use curl to download the input for the current day
  curl -H "Cookie: session=$SESSION_COOKIE" -o "$OUTPUT_FILE" "https://adventofcode.com/$YEAR/day/$DAY_NUMBER/input"

  # Check if the file was downloaded successfully
  if [[ -s "$OUTPUT_FILE" ]]; then
    echo "Day $DAY_NUMBER input saved to $OUTPUT_FILE"
  else
    echo "Failed to download input for Day $DAY_NUMBER. Check your session cookie and network connection."
    rm -f "$OUTPUT_FILE" # Remove the empty file if the download failed
  fi
done

