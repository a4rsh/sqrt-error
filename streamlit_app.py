import streamlit as st
import numpy as np
import plotly.express as px
import sqrt
import math

domain_min, domain_max = st.slider("Domain of plot:", 1, 1000, (1, 1000), 1)
approximation_degree = st.slider("Degree of approximation:", 0, 10, 1, 1)

x = np.linspace(domain_min, domain_max, (domain_max - domain_min) * 2)

def sqrt_error(domain, terms):
    output = domain.copy()
    for index in range(len(output)):
        output[index] = math.fabs(math.sqrt(output[index]) - sqrt.sqrt(output[index], terms))
    return output

y = sqrt_error(x, approximation_degree)

df = px.data.iris()
fig = px.line(df, x, y, title="Error of Square Root Approximation")

st.plotly_chart(fig)
