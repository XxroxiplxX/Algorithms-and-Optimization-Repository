using DelimitedFiles, JuMP, GLPK, LinearAlgebra

cost = readdlm("dataset/shortest-path/costs.txt")
time = readdlm("dataset/shortest-path/times.txt")
matrix = readdlm("dataset/shortest-path/matrix.txt")

n = 5#size(costs[1])
start = 1
finish = 3
T = 15
#print(graph)
shortest_path = Model(GLPK.Optimizer)
@variable(shortest_path, 0 <= path[i=1:n, j=1:n] <= 1, Int)


@constraint(shortest_path, [i in 1:n, j in 1:n; matrix[i,j] == 0], path[i, j] == 0)


@constraint(shortest_path, sum(path[start, :]) - sum(path[:, start]) == 1)


@constraint(shortest_path, sum(path[finish, :]) - sum(path[:, finish]) == -1)

@constraint(shortest_path, [i = 1:n; i != start && i != finish], sum(path[i, :]) == sum(path[:, i]))

@constraint(shortest_path, sum(path[i,j]*time[i,j] for i in 1:n, j in 1:n) <= T)

@objective(shortest_path, Min, sum(path[i,j]*cost[i,j] for i in 1:n, j in 1:n))

optimize!(shortest_path)
@show termination_status(shortest_path)
@show value.(path)