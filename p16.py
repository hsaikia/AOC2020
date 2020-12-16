def flatten(a):
    return "".join(a)

def process(field_to_rules_dict, val):
    for rule in field_to_rules_dict.values():
        if satisfies(rule, val):
            return True
    return False

def satisfies(constraints, val):
    for [min_val, max_val] in constraints:
        if val >= min_val and val <= max_val:
            return True
    return False

def assign(field_to_indices_dict, field_to_column_dict):
    val = None
    name = None
    for k, v in field_to_indices_dict.items() :
        if len(v) == 1 :
            val = v[0]
            name = k
            break
            
    for k, v in field_to_indices_dict.items():
        if val in v :
            v.remove(val)
            field_to_indices_dict[k] = v
    
    del field_to_indices_dict[name]

    field_to_column_dict[name] = val
    
    return field_to_indices_dict, field_to_column_dict

def main():
    file = open("input.txt", "r")
    #file = open("sample_input.txt", "r")
    inp = [line.strip().split(' ') for line in file.readlines() if line.strip()]

    field_to_rules_dict = dict()

    for x in inp:
        if 'or' in x :
            name = flatten(x[:-3])
            r1 = [int(y) for y in x[-3].split('-')]
            r2 = [int(y) for y in x[-1].split('-')]
            field_to_rules_dict[name] = [r1, r2]

    mine = []
    others = []

    other_start = False
    my_start = False

    # part 1
    ans = 0
    for x in inp :
        if my_start :
            fields_str = x[0].split(',')
            mine = [int(field_str) for field_str in fields_str]
            my_start = False
        if other_start :
            fields_str = x[0].split(',')
            fields = [int(field_str) for field_str in fields_str]
            invalid = False
            for value in fields :
                ret = process(field_to_rules_dict, value)
                if ret == False :
                    invalid = True
                    ans += value
                    break
            if invalid == False:        
                others.append(fields)
        if 'nearby' in x :
            other_start = True
            my_start = False
        if 'your' in x:
            my_start = True

    print(f"Part 1 answer {ans}")

    num_tickets = len(others)
    num_types = len(others[0])

    field_to_indices_dict = {name:[] for name in field_to_rules_dict.keys()}

    for idx in range(num_types):
        for name, rule in field_to_rules_dict.items():
            count = 0
            for i in range(num_tickets):
                count += satisfies(rule, others[i][idx])
            if count == num_tickets:
                field_to_indices_dict[name].append(idx)

    field_to_column_dict = {name:-1 for name in field_to_rules_dict.keys()}

    while field_to_indices_dict:
        field_to_indices_dict, field_to_column_dict = assign(field_to_indices_dict, field_to_column_dict)

    print(f"Resolved Ticket fields and column indices {field_to_column_dict}")

    # part 2
    ans = 1
    for name, col in field_to_column_dict.items():
        if name[0:4] == 'depa':
            ans *= mine[col]

    print(f"Part 2 answer {ans}")


if __name__ == "__main__":
    main()