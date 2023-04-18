using DelimitedFiles, Random

rng = MersenneTwister(1000)
size = 7
costs = zeros(size,size)
times = zeros(size,size)
for i in 1:size, j in 1:size
    if rand(rng) < 0.5
        times[i,j] = 0
        costs[i,j] = 0
    else
        times[i,j] = 0.001 + rand(rng)
        times[i,j] *= 10000
        costs[i,j] = 1000/times[i,j]
    end
end
writedlm("dataset/shortest-path/costs.txt", costs)
writedlm("dataset/shortest-path/times.txt", times)