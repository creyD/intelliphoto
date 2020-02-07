import sys
from datetime import datetime
from collections import Counter
import random

timepoints = []
weeks = []

factors = {
    "Conrad": 1/3,
    "Paul": 2,
    "Basti": 3/2
}

summands_min = {
    "Paul": 20
}

summands_max = {
    "Paul": 300
}

def newCounter():
    return Counter({
            "Conrad": 0,
            "Paul": 0,
            "Basti": 0,
            "Seb": 0,
            "Mucke": 0,
            "Jan": 0
        })

class AuthorTimepoint:
    def __init__(self, line):
        parts = line.split()
        self.time = datetime.fromtimestamp(int(parts[0]))
        self.lines = Counter({
            "Conrad": int(parts[1]) + int(parts[9]),
            "Paul": int(parts[6]),
            "Basti": int(parts[5]) + int(parts[8]),
            "Seb": int(parts[7]) + int(parts[11]),
            "Mucke": int(parts[2]) + int(parts[4]),
            "Jan": int(parts[3]) + int(parts[10])
        })

class AuthorWeek:
    def __init__(self, week, lines):
        self.week = week
        self.lines = lines
    
    def __repr__(self):
        all = {**dict(newCounter()), **dict(self.lines)}
        final = {}
        numZeros = 0

        for line_c in all.values():
            if line_c == 0:
                numZeros += 1

        print(all)
        print(f"numZeros: {numZeros}")

        for person, peline in all.items():
            # print(person)
            fac = factors.get(person, 1)

            if numZeros > 2 and peline == 0:
                final[person] = 0
            else:
                sum_n = summands_min.get(person, 0)
            
                if sum_n != summands_max.get(person, 0):
                    sum_n = random.randrange(sum_n, summands_max.get(person, 0))
                
                final[person] = min(int(fac * (peline + sum_n)), 7000)

        print("final.values")
        print(final.values())
        finished_line = str(self.week) + " " + " ".join([str(v) for v in final.values()])
        print(finished_line)
        return finished_line

if __name__ == "__main__":
    if len(sys.argv) >= 3:
        with open(sys.argv[1], "r", encoding="utf-8") as f:
            for line in f:
                timepoints.append(AuthorTimepoint(line))

        cur_week = ""
        lines_week = newCounter()
        last_lines = newCounter()

        for timepoint in timepoints:
            elem_week = timepoint.time.isocalendar()[1]

            if cur_week != elem_week:
                if cur_week:
                    weeks.append(AuthorWeek(cur_week, lines_week))
                lines_week = newCounter()
                cur_week = elem_week

            lines_week += timepoint.lines - last_lines
            last_lines = timepoint.lines

        with open(sys.argv[2], "w", encoding="utf-8") as f:
            f.write("KW" + " " + " ".join(newCounter().keys()) + "\n")
            for week in weeks:
                f.write(str(week) + "\n")   
    else:
        print("Not enough arguments.")
    

