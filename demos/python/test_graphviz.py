
import pygraphviz as pgv
import re

ir = open("asr.txt", "r").read()

def viz(file):
    g = pgv.AGraph(directed=True, strict=True)
    g.node_attr["shape"] = "box"
    g.node_attr["style"] = "filled,rounded" 
    g.node_attr["fillcolor"] = "cornsilk" 
 
            
    with open(file, 'r') as f:
        for line in f.readlines():
            ret = re.findall('%[0-9a-zA-Z.]+', line)
            if ret:
                ret = [ i.split('.')[0][1:] for i in ret]
                if not g.has_node(ret[0]): 
                    g.add_node(ret[0])
                for src in ret[1:]: 
                    if not g.has_node(src): 
                        g.add_node(src)
                    g.add_edge(src, ret[0])

    g.layout(prog='dot')
    g.draw('a.dot')
    print('----------')
 

viz ("asr.txt")

def pgv_from_gdef(gdef, dotfile):
    g = pgv.AGraph(directed=True, strict=True)
    g.node_attr["shape"] = "box"
    g.node_attr["style"] = "filled,rounded" 
    g.node_attr["fillcolor"] = "cornsilk" 

    subE = g.add_subgraph(label="embedding", name='cluster_embedding')
    sub0 = g.add_subgraph(label="layer_0", name='cluster_layer0')
    sub1 = g.add_subgraph(label="layer_1", name='cluster_layer1')
    
    name_op_map = { x.name: x.op for x in gdef.node}
    name_idx_map = {}
    for idx,node in enumerate(gdef.node):
        if node.op != 'Const':
            name_idx_map[node.name] = idx 
    
    def get_color(op):
        if 'MatMul' in op: return 'orange'
        if op =='Const': return 'grey'
        if op =='QuantizeV2': return 'green'
        if op =='Softmax': return 'purple'
        return 'cornsilk'
    for node in gdef.node: 
        if node.op != 'Const':
            if 'embedding' in node.name:
                subE.add_node(name_idx_map[node.name], label=node.op, tooltip=node.name, fillcolor=get_color(node.op)) 
            elif 'layer_0' in node.name:
                sub0.add_node(name_idx_map[node.name], label=node.op, tooltip=node.name, fillcolor=get_color(node.op)) 
            elif 'layer_1' in node.name:
                sub1.add_node(name_idx_map[node.name], label=node.op, tooltip=node.name, fillcolor=get_color(node.op)) 
            else:
                g.add_node(name_idx_map[node.name], label=node.op, tooltip=node.name, fillcolor=get_color(node.op)) 
    for node in gdef.node: 
        for inop in node.input:
            if inop in  name_idx_map.keys(): 
                g.add_edge(name_idx_map[inop], name_idx_map[node.name]) 

    g.layout(prog='dot')
    g.draw('a.dot')
    print('----------')
