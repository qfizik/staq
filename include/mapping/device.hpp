/*-------------------------------------------------------------------------------------------------
| This file is distributed under the MIT License.
| See accompanying file /LICENSE for details.
| Author(s): Matthew Amy
*------------------------------------------------------------------------------------------------*/

#include <vector>
#include <map>

namespace synthewareQ {
namespace mapping {

  /* \brief! Definition of physical devices for efficient mapping */

  class device {
  public:
    device(std::string name, size_t n, std::vector<std::pair<size_t, size_t> >& dag)
      : name_(name)
      , qubits_(n)
      , couplings_(dag)
    {
      single_qubit_fidelities.resize(n);
      for (auto i = 0; i < n; i++) {
        single_qubit_fidelities[i] = 1.0;
      }

      for (auto pair : couplings) {
        coupling_fidelities[pair] = 1.0;
      }
    }
    device(std::string name, size_t n, std::vector<std::vector<bool> >& dag,
           std::vector<double>& sq_fi, std::vector<std::vector<double> >& tq_fi)
      : name_(name)
      , qubits_(n)
      , couplings_(dag)
      , single_qubit_fidelities(sq_fi)
      , coupling_fidelities(tq_fi)
    {}

    std::string name_;
    size_t qubits_;

    bool coupled(size_t i, size_t j) {
      if (0 <= i && i < qubits_ && 0 <= j && j < qubits) return couplings_[i][j];
      else throw std::out_of_range("Qubit(s) not in range");
    }

    double sq_fidelity(size_t i) {
      if (0 <= i && i < qubits_) return single_qubit_fidelities[i];
      else throw std::out_of_range("Qubit not in range");
    }
    double tq_fidelity(size_t i, size_t j) {
      if (coupled(i, j)) return coupling_fidelities[i][j];
      else throw std::logic_error("Qubit not coupled");
    }

  private:
    std::vector<std::vector<bool> > couplings_;
    std::vector<double> single_qubit_fidelities_;
    std::vector<std::vector<double> > coupling_fidelities_;

  };

  device rigetti_8q(
    "Rigetti 8Q",
    8,
    { {0, 1, 0, 0, 0, 0, 0, 1},
      {1, 0, 1, 0, 0, 0, 0, 0},
      {0, 1, 0, 1, 0, 0, 0, 0},
      {0, 0, 1, 0, 1, 0, 0, 0},
      {0, 0, 0, 1, 0, 1, 0, 0},
      {0, 0, 0, 0, 1, 0, 1, 0},
      {0, 0, 0, 0, 0, 1, 0, 1},
      {1, 0, 0, 0, 0, 0, 1, 0},},
    { 0.957, 0.951, 0.982, 0.970, 0.969, 0.962, 0.969, 0.932 },
    { {0, 0.92, 0, 0, 0, 0, 0, 0.92},
      {0.91, 0, 0.91, 0, 0, 0, 0, 0},
      {0, 0.82, 0, 0.82, 0, 0, 0, 0},
      {0, 0, 0.87, 0, 0.87, 0, 0, 0},
      {0, 0, 0, 0.67, 0, 0.67, 0, 0},
      {0, 0, 0, 0, 0.93, 0, .093, 0},
      {0, 0, 0, 0, 0, 0.93, 0, 0.93},
      {0.91, 0, 0, 0, 0, 0, 0.91, 0},}
  );
    

}
}
