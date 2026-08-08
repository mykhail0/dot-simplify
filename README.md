# dot-simplify

A project that lets you simplify graph descriptions in a sublanguage of DOT.

(<https://dreampuf.github.io/GraphvizOnline/>)

The data language and language of the program result are described below using context-free grammar in the extended BNF notation:

    the names of the auxiliary symbols are identifiers composed of lowercase letters,

    the names of the final symbols are identifiers composed of capital letters,

    strings included in quotes are anonymous end symbols,

    the initial symbol is the auxiliary symbol on the left side of the first production,

    between the left and right side of production is the sign =,

    At the end of production there is a sign ;,

    sign |symbolizes the alternative,

    a fragment that can repeat itself zero or more times is included in the brace brackets { ... }.

The data syntax is the word of the language described by grammar:

graf = "strict" "digraph" podgraf ;
podgraf = "{" { węzły { "->" węzły } } "}" ;
węzły = ID | podgraf ;

At the program's entry, anonymous end symbols correspond to the strings of characters that in grammar are included in quotes.

The equivalent of the end symbol IDa decimally negative integer is recorded without insignificant leading zeros.

In the program data, before and after the final symbols, can occur, in any number, spaces and ends of the row.

The data of the program describes the directed graph (digraph) without multiple edges (strict).

The graph has a hierarchical structure. It consists of subgraphs, which can be freely nested.

Subgraphs are not separate. A knot or edge can belong to multiple subgraphs.

Each knot and every edge of the subgraph also belongs to the graph in which this subgraph is nested.

The graph node is unequivocally represented by a non-negative integer ID, hereinafter referred to as the node number.

Symbol ->indicates between which graph nodes are the edges:

    if before or after ->There is a single knot w, this interpretation is the same as if instead of wthere was an infinity subgraph in which wis one knot,

    record G -> H, where Gand Hare subgraphs, indicates that for each node usubgraph Gand for every node wsubgraph H, in the graph is directed edge from uto w.

The program data language described here is a subset of the DOT language. If there are doubts about the interpretation of the data, it can be checked with the program dotor the service to which the link in the introduction is.
Program result

The result of the program is described by grammar:

graf = "digraph" "{" { ID "->" "{" { ID } "}" } "}" ;

The first row of the result is in the form of:

digraph {

The last row of the result is in the form of:

}

Between the first and last rows there is one line for each graph node. These poems are sorted in order of growing node numbers.

A poem for a knot wIt starts with the number of this node. After that, there's a space, signs ->, another space and a sign {. At the end of the poem is a space and a sign }.

Between the buckles is, orderly growing, a string of node numbers to which there is an edge from the node w. Each of these numbers is preceded by one space.
Examples
