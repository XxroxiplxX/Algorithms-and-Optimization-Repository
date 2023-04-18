using DelimitedFiles, GLPK, JuMP

#=
G = [
#   s1    s2   s3
    10    7    8;  #a1 [1,3] = s1 -> a1
    10    11   14; #a2
    9     12   4;  #a3
    11    13   9;  #a4
]

n = 3
m = 4
suppliers = []
airports = []
=#
G = readdlm("dataset/min-cost-flow/costs.txt")
suppliers = readdlm("dataset/min-cost-flow/suppliers.txt")
airports = readdlm("dataset/min-cost-flow/airports.txt")
n = length(suppliers)
m = length(airports)
min_cost_flow = Model(GLPK.Optimizer)

@variable(min_cost_flow, f[1:m,1:n] >= 0)

#balance of suppliers
@constraint(min_cost_flow, [i = 1:m], sum(f[i,:]) == airports[i])
#balance od airports
@constraint(min_cost_flow, [i = 1:n], sum(f[:,i]) <= suppliers[i])
@objective(min_cost_flow, Min, sum(G[i, j] * f[i, j] for i in 1:m, j in 1:n))

optimize!(min_cost_flow)
@show objective_value(min_cost_flow);
@show value.(f);


    



