import sys
from basicDataStructure import Graph, ResourceLibrary, Resource, CostTable
from ILPSolver import exactILPScheduling
import re
import pdb

max_latency = 15

#Creates a graph based on the dependencies specified in sm.g
def createGraph(graphfile):
	name=re.split('\.',graphfile)[0]
	graphobj=Graph(name=name)
	f=open(graphfile,'r')
	lines=f.readlines()
	for line in lines:
		if "->" in line:
			[headname,tailname] = re.split('->',line)
			headname = headname.strip()
			tailname = tailname.strip()
			headnode = graphobj.addNode(headname)
			tailnode = graphobj.addNode(tailname)
			graphobj.createEdge(head=headnode,tail=tailnode)
			headnode.asap=1
			headnode.alap=max_latency
			tailnode.asap=1
			tailnode.alap=max_latency

	graphobj.getSourceSink()
	f.close()
	return graphobj

#Creates a cost mapping table based on the resource configuration specified in sm.cm 
def generateCostMappingTable(costfile,graphobj):
	name=re.split('\.',costfile)[0]
	reslib = ResourceLibrary(name=name)
	ct = CostTable(name=name)
	f=open(costfile,'r')
	lines=f.readlines()
	for line in lines:
		if not re.match('\S',line): #empty string
			continue
		if re.match('^;',line): # comment
			continue

		if not ":" in line:  # resource info
			[resname,latency,number,area] = re.split(" ",line)
			resname=resname.strip()
			latency=int(latency.strip())
			area = int(area.strip())
			res = Resource(name=resname,latency=latency,number=number,area=area)
			reslib.resources.append(res)
			reslib.resourcehash[res.name]=res
			ct.resources.append(res)
			
		else: # mapping info
			[resname,nodenames] = re.split(":",line)
			nodenames=nodenames.strip()
			resname=resname.strip()
			resource = reslib.resourcehash[resname]
			ct.res_nodes[resource]=[]
			for nodename in re.split(" ",nodenames):
				nname=nodename.strip()
				node = graphobj.nodehash[nname]
				if not node in ct.nodeRes_table.keys():
					ct.nodeRes_table[node]=[]
					ct.nodes.append(node)
				ct.nodeRes_table[node].append(resource)

				if not node in ct.res_nodes[resource]:
					ct.res_nodes[resource].append(node)

	f.close()
	return ct

if __name__ == '__main__':
	if (len(sys.argv) != 3):
		print("usage : python {exefile} graphfile costfile".format(exefile=sys.argv[0])) #checks if sm.g and sm.c are passed as arguments
		exit(-1)
	
	graphfile=sys.argv[-2] 
	costfile=sys.argv[-1]

	graphobj = createGraph(graphfile)
	graphobj.printOutDot(filename='./results/{name}.dot'.format(name=graphobj.name)) # generates a .dot graph that can be read using Graphviz

        ct = generateCostMappingTable(costfile,graphobj) 
	ct.printCostTable()
	
	exactILPScheduling(graphobj,ct,ASAP=False, ALAP=False) #This function (inside ILPSolver.py) writes out the ILP formation of the problem using the graph and cost mapping table





