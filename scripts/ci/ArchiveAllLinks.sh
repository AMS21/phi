#!/usr/bin/env bash

set -u

# Regex for html
# Copied from here https://stackoverflow.com/a/3184819/10114628
regex='(https?|ftp)://[-A-Za-z0-9\+&@#/%?=~_|!:,.;]*[-A-Za-z0-9\+&@#/%=~_|]'

echo "Scanning all files in \"$(pwd)\"..."

all_files=$(find . -type f ! -path "./.git/*" -exec grep -Iq . {} \; -print)

# 12 Request per minute. Archive.org asks for no more than 15 requests per minute
# https://archive.org/details/toomanyrequests_20191110
sleep_time=5s

# Iterate over each file
for file in $all_files; do
    echo "Analyzing file: \"$file\""

    # Read file line by line
    while read -r line; do
        # For each word in that line
        for word in $line; do
            # Regex for weblink
            if [[ $word =~ $regex ]]; then
                # Sleep so we don't spam the server
                sleep "$sleep_time"

                link="${BASH_REMATCH[0]}"
                echo "Archiving link: \"$link\""

                # Perform curl request
                response=$(curl -s -I "https://web.archive.org/save/$link")

                # Get response code
                response_code=$(echo "$response" | grep --ignore-case "HTTP/" | cut -d' ' -f2)

                # Check response code
                if [[ "$response_code" == "302" ]]; then
                    # Success
                    location=$(echo "$response" | grep --ignore-case "Location: https" | cut -d' ' -f2)

                    echo "Archived link:  \"$location\""
                elif [[ "$response_code" == "429" ]]; then
                    # Too many requests
                    echo "WARN: Sending too many requests!"
                else
                    # Unknown
                    echo "WARN: Unknown error"
                    echo "WARN: Response code: $response_code"
                    echo "WARN: Full curl response"
                    echo "$response"
                fi
            fi
        done
    done <"$file"
done

echo "Finished archiving!"
