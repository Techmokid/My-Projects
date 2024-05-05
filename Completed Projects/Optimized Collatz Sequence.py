import multiprocessing,psutil,math

# ASSISTED BY CHATGPT
# I was struggling to work out the optimization where a sequence value would jump out or end early the moment
# it dipped below the first value (Already computed by another process). I came up with the optimization idea,
# ChatGPT4 just helped me write it
def collatz_sequence_batch(numbers):
    results = []
    for n in numbers:
        original_n = n
        steps = 1
        while n != 1:
            if n % 2 == 0:
                n = n // 2
            else:
                n = 3 * n + 1
            steps += 1
            if n < original_n:
                results.append((steps, n))
                break
        else:
            results.append((steps, None))
    return results

def process_numbers(range_start, range_end, batch_size):
    results = {}
    with multiprocessing.Pool(processes=multiprocessing.cpu_count()) as pool:
        batches = [range(i, min(i+batch_size, range_end)) for i in range(range_start, range_end, batch_size)]
        batch_results = pool.map(collatz_sequence_batch, batches)
        # Flatten results
        for batch in batch_results:
            for number, result in zip(range(batch[0][0], batch[0][0]+len(batch)), batch):
                results[number] = result
    return results

def finalize_sequences(results):
    final_results = {}
    for number, (steps, smaller_number) in results.items():
        if smaller_number and smaller_number in results:
            total_steps = steps + results[smaller_number][0] - 1
        else:
            total_steps = steps
        final_results[number] = total_steps
    return final_results

def get_memory_info():
    mem = psutil.virtual_memory()
    total_ram = mem.total / math.pow(1024,3)
    available_ram = mem.available / math.pow(1024,3)
    return total_ram, available_ram








_,memAvailable = get_memory_info()
range_start, range_end = 1, 10000001*math.floor(memAvailable-1)  # Calculate for 1 to 1,000,000,000
batch_size = 100000
    
print("Starting computation...")
print("This will punish your CPU's cores as hard as python can handle")
print("Due to this, your CPU fans will probably rev up and down")
results = process_numbers(range_start, range_end, batch_size)
    
print("Finalizing sequences...")
final_results = finalize_sequences(results)
    
# Print some results to verify or calculate statistics, such as max sequence length
max_length = max(final_results.values())
print("The maximum sequence length found: " + str(max_length))
