using DelimitedFiles, JuMP, GLPK, LinearAlgebra

costs = readdlm("dataset/shortest-path/costs.txt")
times = readdlm("dataset/shortest-path/times.txt")
n = 7#size(costs[1])
shortest_path = Model(GLPK.Optimizer)
source = 3
dest = 7
T = 1000000
@variable(shortest_path, route[1:n,1:n], Bin)

@constraint(shortest_path, [i = 1:n, j = 1:n; times[i,j] == 0], route[i,j] == 0)
@constraint(shortest_path, [i = 1:n, j = 1:n; i != source && i != dest], sum(route[i,:]) == sum(route[:,i]))
@constraint(shortest_path, sum(route[source,:]) - sum(route[:,source]) == 1)
@constraint(shortest_path, sum(route[dest,:]) - sum(route[:,dest]) == -1)
constraint(model, sum(route[i,j] for i in 1:n, j in 1:n) <= T)
@objective(shortest_path, Min, sum(route[i,j]*costs[i,j] for i in 1:n, j in 1:n))
optimize!(shortest_path)
@show objective_value(route)
@show value.(route)