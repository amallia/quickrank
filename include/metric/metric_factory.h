/*
 * QuickRank - A C++ suite of Learning to Rank algorithms
 * Webpage: http://quickrank.isti.cnr.it/
 * Contact: quickrank@isti.cnr.it
 *
 * Unless explicitly acquired and licensed from Licensor under another
 * license, the contents of this file are subject to the Reciprocal Public
 * License ("RPL") Version 1.5, or subsequent versions as allowed by the RPL,
 * and You may not copy or use this file in either source code or executable
 * form, except in compliance with the terms and conditions of the RPL.
 *
 * All software distributed under the RPL is provided strictly on an "AS
 * IS" basis, WITHOUT WARRANTY OF ANY KIND, EITHER EXPRESS OR IMPLIED, AND
 * LICENSOR HEREBY DISCLAIMS ALL SUCH WARRANTIES, INCLUDING WITHOUT
 * LIMITATION, ANY WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR
 * PURPOSE, QUIET ENJOYMENT, OR NON-INFRINGEMENT. See the RPL for specific
 * language governing rights and limitations under the RPL.
 *
 * Contributor:
 *   HPC. Laboratory - ISTI - CNR - http://hpc.isti.cnr.it/
 */
#pragma once

#include <iostream>
#include <climits>
#include <memory>

#include "types.h"

#include "metric/ir/tndcg.h"
#include "metric/ir/ndcg.h"
#include "metric/ir/dcg.h"
#include "metric/ir/map.h"
#include "metric/ir/rmse.h"

namespace quickrank {
namespace metric {
namespace ir {

std::shared_ptr<Metric> ir_metric_factory(std::string metric,
                                          size_t cutoff) {
  std::transform(metric.begin(), metric.end(),
                 metric.begin(), ::toupper);
  if (metric == Dcg::NAME_)
    return std::shared_ptr<Metric>(new Dcg(cutoff));
  else if (metric == Ndcg::NAME_)
    return std::shared_ptr<Metric>(new Ndcg(cutoff));
  else if (metric == Tndcg::NAME_)
    return std::shared_ptr<Metric>(new Tndcg(cutoff));
  else if (metric == Map::NAME_)
    return std::shared_ptr<Metric>(new Map(cutoff));
  else if (metric == Rmse::NAME_)
    return std::shared_ptr<Metric>(new Rmse(cutoff));
  else
    return std::shared_ptr<Metric>();
}

}  // namespace ir
}  // namespace metric
}  // namespace quickrank
