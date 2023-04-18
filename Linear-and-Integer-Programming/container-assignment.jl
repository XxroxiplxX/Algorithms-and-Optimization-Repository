using GLPK, JuMP, DelimitedFiles
#4
k = 1
#m rows, n columns
containers = readdlm("dataset/containers-assignment/containers.txt", Bool)
m = size(containers, 1)
n = size(containers, 2)


assignment = Model(GLPK.Optimizer)

@variable(assignment, cameras[1:m,1:n], Bin)
#cameras cannot be located at container area
@constraint(assignment, [i in 1:m, j in 1:n; containers[i,j]], cameras[i, j] == 0)
#containers must be in range of cameras

@constraint(assignment, [i in 1:m, j in 1:n; containers[i,j]], sum(cameras[i, x] for x in max(1, j-k):min(n, j+k)) + sum(cameras[x, j] for x in max(1,i-k):min(m,i+k)) >= 1)

@objective(assignment, Min, sum(cameras[i,j] for i in 1:n, j in 1:m))

optimize!(assignment)
@show objective_value(assignment);
@show value.(cameras);